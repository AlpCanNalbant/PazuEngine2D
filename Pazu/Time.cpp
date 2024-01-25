#include <iostream>
#include "Time.hpp"
#include "World.hpp"

namespace Pazu
{
	void Time::Initialize()
	{
		ActiveWorld->SetObject(this);
	}

	int Time::GetFps(bool *show)
	{
		if (show) *show = false;
		fpsFrames++;
		if (fpsLasttime < SDL_GetTicks() - 1.0 * 1000)
		{
			fpsLasttime = SDL_GetTicks();
			fps = fpsFrames;
			fpsFrames = 0;
			if (show) *show = true;
		}
		return fps;
	}

	float Time::GetDelta() const
	{
		return deltaTime;
	}

	void Time::Update()
	{
		deltaLast = deltaNow;
		deltaNow = SDL_GetPerformanceCounter();

		deltaTime = ((deltaNow - deltaLast) * 1000 / (float)SDL_GetPerformanceCounter());
	}
}
