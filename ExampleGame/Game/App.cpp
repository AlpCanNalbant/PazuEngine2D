#include "App.hpp"
#include "WinAPICommon.hpp"
#include "State.hpp"

App::App(const Pazu::Configuration &config)
	: Pazu::Application{config}, camera{std::make_shared<Pazu::Camera>(mathfu::vec2{35.0f, -5.0f})}, camController{std::make_shared<CameraController>(camera, input)} {}

void App::Initialize()
{
	// If you don't set the path, you won't get any log output from the WinAPICommon library.
	Wcm::Log->OutputFile = Wcm::GetBaseDirectory() / "ExampleGame.log";

	SetVsync(true);
	// resource->SetRelativeMode(false);
	// resource->SetBasePath({Wcm::GetBaseDirectory() / "Assets", "Assets"});
	resource->SetBasePath("Assets"); // By default relative mode is true.
	stateMgr->AddState(new State(resource, camera, input, time));
}

void App::Load()
{
}

void App::PreUpdate()
{
}

void App::Update()
{
	const float dt = time->GetDelta() * 3600.0f;
	if (input->IsKeyDown(SDLK_ESCAPE))
	{
		exitApp = true;
	}

	camController->Update(dt);

	bool show;
	int fps = time->GetFps(&show);
	if (show)
	{
		Wcm::Log->Info("FPS: " + std::to_string(fps));
	}
}

void App::PreRender()
{
}

void App::Render()
{
}

void App::Resize(int width, int height)
{
	Wcm::Log->Info("Window is resized.").Sub("Width", std::to_string(width)).Sub("Height", std::to_string(height));
}

void App::Destroy()
{
}

void App::Focused()
{
	Wcm::Log->Info("Window is focuse.");
}

void App::Unfocused()
{
	Wcm::Log->Info("Window is unfocuse.");
}
