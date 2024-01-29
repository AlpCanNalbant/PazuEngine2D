// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#include "SDL2/SDL.h"
#include "World.hpp"
#include "Camera.hpp"
#include "Sprite.hpp"
#include "StateManager.hpp"
#include "Time.hpp"
#include "Input.hpp"

namespace Pazu
{
	World* ActiveWorld = nullptr;

	void World::Initialize()
	{
		SDL_GetWindowSize(SDL_GL_GetCurrentWindow(), &windowWidth, &windowHeight);
		ActiveWorld = this;
	}

	void World::Update() const
	{
		time->Update();
		input->Update();
		stateManager->Update();
	}

	void World::Render() const
	{
		for (std::size_t i = 0; i < sprites.size() && !sprites[i]->rendererDisable; ++i)
		{
			sprites[i]->Render(activeCamera);
		}
	}

	void World::Resize(int width, int height)
	{
		windowWidth = width;
		windowHeight = height;
		activeCamera->SetOrthoProjection(windowWidth, windowHeight);
		stateManager->Resize(width, height);
	}
}
