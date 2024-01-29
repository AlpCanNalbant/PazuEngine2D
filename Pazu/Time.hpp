// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_timer.h"

namespace Pazu
{
	class Time
	{
	public:
		void Initialize();
		int GetFps(bool *show = nullptr);
		float GetDelta() const;
		void Update();

	private:
		// Fps
		int fpsFrames{0};
		int fps{0};
		int fpsLasttime{SDL_GetTicks()};

		// Delta
		Uint64 deltaNow{SDL_GetPerformanceCounter()};
		Uint64 deltaLast{0};
		float deltaTime{0.0f};
	};
}
