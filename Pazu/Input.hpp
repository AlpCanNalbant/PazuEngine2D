// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once
#include <unordered_map>
#include "SDL2/SDL.h"

namespace Pazu
{
	class Input
	{
	public:
		void Initialize();
		void Update();
		bool IsMouseDown(Uint8 button);
		bool IsMouseHit(Uint8 button);
		bool IsMouseUp(Uint8 button);
		bool IsKeyDown(SDL_Keycode key);
		bool IsKeyHit(SDL_Keycode key);
		bool IsKeyUp(SDL_Keycode key);
		bool IsMouseMoved() const;
		bool IsMouseScrolled() const;
		mathfu::vec2 GetMousePosition() const;
		mathfu::vec2i GetMouseDelta();
		int GetMouseWheelDelta();
		void SetMousePosition(int x, int y);
		void SetMouseCursorVisible(int toggle);
		void SetRelativeMouseMode(bool enabled);

	private:
		SDL_Window* window;
		std::unordered_map<SDL_Keycode, bool> keyMap;
		std::unordered_map<SDL_Keycode, bool> oldKeyMap;
		std::unordered_map<Uint8, bool> mouseButtonMap;
		std::unordered_map<Uint8, bool> oldMouseButtonMap;
		int mouseWheelDelta{0};
		Uint32 eventType{0};
		int xrel{0}, yrel{0};
	};
}
