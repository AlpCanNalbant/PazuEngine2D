#include <iostream>
#include "GL/glew.h"
#include "Application.hpp"

namespace Pazu
{
	Application::Application(const Configuration &config)
		: world{std::make_shared<World>()}, stateMgr{std::make_shared<StateManager>()}, resource{std::make_shared<ResourceManager>()}, input{std::make_shared<Input>()}, time{std::make_shared<Time>()}
	{
		Wcm::Log->OutputFile = Wcm::GetBaseDirectory() / "Log.txt";
		std::cout << "Pazu Engine 2D is has been started." << std::endl;
    	Wcm::Log->Info("Pazu Engine 2D is has been started.");

		if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
		{
			std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
			Wcm::Log->Error("Failed to initialize SDL.").Sub("SDLError", SDL_GetError());
			return;
		}

		Uint32 flags;
		int w, h;
		if (config.fullScreen)
		{
			SDL_DisplayMode dm;
			SDL_GetCurrentDisplayMode(0, &dm);

			flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
			w = dm.w;
			h = dm.h;
		}
		else
		{
			w = config.width;
			h = config.height;

			flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
			if (config.borderless)
			{
				flags |= SDL_WINDOW_BORDERLESS;
			}
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, config.depthBits);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, config.stencilBits);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, config.antialiasingLevel);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

		if (auto rawWindow = SDL_CreateWindow(config.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags))
		{
			window = {rawWindow, SDL_DestroyWindow};
		}
		else
		{
			std::cout << "Failed to create SDL window: " << SDL_GetError() << std::endl;
			Wcm::Log->Error("Failed to create SDL window.").Sub("SDLError", SDL_GetError());
			return;
		}

		SDL_GL_CreateContext(window.get());

		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			std::cout << "Failed to initialize GLEW: " << glewGetErrorString(err) << std::endl;
			Wcm::Log->Error("Failed to initialize GLEW.").Sub("GLEWError", reinterpret_cast<const char *>(glewGetErrorString(err)));
			return;
		}
		glewGetExtension("GL_VERSION_3_3");

		glViewport(0, 0, config.width, config.height);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		world->Initialize();
		stateMgr->Initialize();
		resource->Initialize();
		input->Initialize();
		time->Initialize();

		std::cout << "Pazu Engine 2D is successfully initialized." << std::endl;
    	Wcm::Log->Info("Pazu Engine 2D is successfully initialized.");
	}

	void Application::Run()
	{
		Initialize();

		while (!exitApp)
		{
			SDL_Event e;
			while (SDL_PollEvent(&e))
			{
				switch (e.type)
				{
				case SDL_WINDOWEVENT_CLOSE:
					exitApp = true;
					break;
				case SDL_WINDOWEVENT_SIZE_CHANGED:
					glViewport(0, 0, e.window.data1, e.window.data2);
					Resize(e.window.data1, e.window.data2);
					break;
				case SDL_WINDOWEVENT_FOCUS_GAINED:
					Focused();
					break;
				case SDL_WINDOWEVENT_FOCUS_LOST:
					Unfocused();
					break;
				}
			}

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			PreRender();
			world->Render();
			Render();

			SDL_GL_SwapWindow(window.get());

			world->Update();
			Update();
		}

		Destroy();

		std::cout << "Pazu Engine 2D is has been ended." << std::endl;
    	Wcm::Log->Info("Pazu Engine 2D is has been ended.");
	}

	void Application::Shutdown()
	{
		exitApp = true;
	}

    void Application::Resize(int width, int height)
    {
		world->Resize(width, height);
    }

	mathfu::vec2i Application::GetWindowPosition() const
	{
		mathfu::vec2i pos;
		SDL_GetWindowPosition(window.get(), &pos.x, &pos.y);
		return pos;
	}

	mathfu::vec2i Application::GetWindowSize() const
	{
		mathfu::vec2i size;
		SDL_GetWindowSize(window.get(), &size.x, &size.y);
		return size;
	}

	void Application::SetVsync(int value)
	{
		SDL_GL_SetSwapInterval(value);
	}
}
