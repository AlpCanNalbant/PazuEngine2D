// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once
#include "SDL2/SDL.h"
#include "Configuration.hpp"
#include "StateManager.hpp"
#include "ResourceManager.hpp"
#include "World.hpp"
#include "Input.hpp"
#include "Time.hpp"

namespace Pazu
{
	class StateManager;
	class ResourceManager;

	class Application
	{
	public:
		Application(const Configuration &config);
		virtual ~Application() = default;
		void Run();
		void Shutdown();
		virtual void Initialize() = 0;
		virtual void Load() = 0;
		virtual void Update() = 0;
		virtual void PreRender() = 0;
		virtual void Render() = 0;
		virtual void Resize(int width, int height);
		virtual void Destroy() = 0;
		virtual void Focused() = 0;
		virtual void Unfocused() = 0;
		mathfu::vec2i GetWindowPosition() const;
		mathfu::vec2i GetWindowSize() const;
		void SetVsync(int value);

		bool exitApp{false};

	protected:
		std::shared_ptr<World> world;
		std::shared_ptr<StateManager> stateMgr;
		std::shared_ptr<ResourceManager> resource;
		std::shared_ptr<Input> input;
		std::shared_ptr<Time> time;

	private:
		std::unique_ptr<SDL_Window, void(*)(SDL_Window *)> window{nullptr, nullptr};
	};
}
