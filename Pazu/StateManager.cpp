#include "StateManager.hpp"
#include "Globals.hpp"
#include "World.hpp"

namespace Pazu
{
	StateManager::StateManager(State* firstState)
		: states{firstState}
	{
		assert(firstState && "First state is cannot be null.");
	}

    StateManager::~StateManager()
	{
		ClearStates();
	}

	void StateManager::ClearStates()
	{
		if (states.empty())
		{
			return;
		}

		for (State* state : states)
		{
			state->Unload();
		}

		SafeDeleteList(states);
	}

	void StateManager::ChangeState(State* state)
	{
		ClearStates();

		states.push_back(state);
		state->Load();
	}

	void StateManager::AddState(State* state)
	{
		if (!states.empty())
		{
			states.back()->Pause();
		}

		states.push_back(state);
		state->Load();
	}

	void StateManager::RemoveState(State* state)
	{
		state->Unload();

		SafeDelete(state);
		states.erase(std::find(states.begin(), states.end(), state));

		if (!states.empty())
		{
			states.back()->Resume();
		}
	}

	void StateManager::Initialize()
	{
		ActiveWorld->SetObject(this);
	}

	void StateManager::Load() const
	{
		if (!states.empty())
		{
			states.back()->Load();
		}
	}

	void StateManager::Resize(int width, int height) const
	{
		states.back()->Resize(width, height);
	}

	void StateManager::Update() const
	{
		states.back()->Update();
	}
}
