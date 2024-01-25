#pragma once

namespace Pazu
{
	class State
	{
	public:
		State() = default;
		State(const State &) = default;
		State(State &&) = default;
		virtual ~State() = default;
		State &operator=(const State &) = default;
		State &operator=(State &&) = default;
		virtual void Load() = 0;
		virtual void Unload() = 0;
		virtual void Pause() = 0;
		virtual void Resume() = 0;
		virtual void Resize(int width, int height) = 0;
		virtual void Update() = 0;
	};
}
