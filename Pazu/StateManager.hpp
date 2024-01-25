#pragma once
#include <vector>
#include "State.hpp"

namespace Pazu
{
	class StateManager
	{
	public:
		StateManager() = default;
		StateManager(State* firstState);
		~StateManager();
		StateManager(const StateManager &) = default;
		StateManager(StateManager &&) = default;
		StateManager &operator=(const StateManager &) = default;
		StateManager &operator=(StateManager &&) = default;
		void ClearStates();
		void ChangeState(State* state);
		void AddState(State* state);
		void RemoveState(State* state);
		void Initialize();
		void Load() const;
		void Resize(int width, int height) const;
		void Update() const;

	private:
		std::vector<State*> states;
	};
}
