#pragma once
#include <vector>
#include <iostream>
#include <memory>

namespace Pazu
{
	class Camera;
	class Sprite;
	class Gui;
	class StateManager;
	class Input;
	class Time;

	class World
	{
	public:
		template <typename T>
		void AddObject(T *obj);
		template <typename T>
		void RemoveObject(T *obj);
		template <typename T>
		void SetObject(T *obj);
		void Initialize();
		void Update() const;
		void Render() const;
		void Resize(int width, int height);

		StateManager *stateManager;
		Input *input;
		Time *time;
		Camera *activeCamera;
		std::vector<Sprite *> sprites;
		int windowWidth, windowHeight;
	};

	extern World* ActiveWorld;
}

#include "World.inl"
