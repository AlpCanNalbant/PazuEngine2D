// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#include <iostream>
#include "Input.hpp"
#include "World.hpp"

namespace Pazu
{
	void Input::Initialize()
	{
		window = SDL_GL_GetCurrentWindow();
		ActiveWorld->SetObject(this);
	}

	void Input::Update()
	{
		eventType = SDL_FIRSTEVENT;
		oldKeyMap = keyMap;
		oldMouseButtonMap = mouseButtonMap;

		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_KEYDOWN:
				keyMap[e.key.keysym.sym] = true;
				break;
			case SDL_KEYUP:
				keyMap[e.key.keysym.sym] = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouseButtonMap[e.button.button] = true;
				break;
			case SDL_MOUSEBUTTONUP:
				mouseButtonMap[e.button.button] = false;
				break;
			case SDL_MOUSEWHEEL:
				mouseWheelDelta = e.wheel.y;
				break;
			case SDL_MOUSEMOTION:
				xrel = e.motion.xrel;
				yrel = e.motion.yrel;
				break;
			}
			eventType = e.type;
		}
	}

	bool Input::IsMouseDown(Uint8 button)
	{
		return mouseButtonMap[button];
	}

	bool Input::IsMouseHit(Uint8 button)
	{
		return mouseButtonMap[button] && !oldMouseButtonMap[button];
	}

	bool Input::IsMouseUp(Uint8 button)
	{
		return !mouseButtonMap[button] && oldMouseButtonMap[button];
	}

	bool Input::IsKeyDown(SDL_Keycode key)
	{
		return keyMap[key];
	}

	bool Input::IsKeyHit(SDL_Keycode key)
	{
		return keyMap[key] && !oldKeyMap[key];
	}

	bool Input::IsKeyUp(SDL_Keycode key)
	{
		return !keyMap[key] && oldKeyMap[key];
	}

	bool Input::IsMouseMoved() const
	{
		return eventType == SDL_MOUSEMOTION;
	}

	bool Input::IsMouseScrolled() const
	{
		return eventType == SDL_MOUSEWHEEL;
	}

	mathfu::vec2 Input::GetMousePosition() const
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		return {x, y};
	}

	mathfu::vec2i Input::GetMouseDelta()
	{
		const auto temp = mathfu::vec2i(xrel, yrel);
		xrel = yrel = 0;
		return temp;
	}

	int Input::GetMouseWheelDelta()
	{
		const auto temp = mouseWheelDelta;
		mouseWheelDelta = 0;
		return temp;
	}

	void Input::SetMousePosition(int x, int y)
	{
		SDL_WarpMouseInWindow(window, x, y);
	}

	void Input::SetMouseCursorVisible(int toggle)
	{
		SDL_ShowCursor(toggle);
	}

	void Input::SetRelativeMouseMode(bool enabled)
	{
		SDL_SetRelativeMouseMode(enabled ? SDL_TRUE : SDL_FALSE);
	}
}
