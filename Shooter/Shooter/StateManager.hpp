#pragma once
#include "Window.hpp"
#include "State.hpp"

class StateManager
{
	private:
		State* m_CurrentState;
	public:
		StateManager();
		~StateManager();

		inline State* GetState() { return StateManager::m_CurrentState; };
		inline void SetState(State* _state) { StateManager::m_CurrentState = _state; };

		template <typename T>
		State* ChangeState()
		{
			StateManager::m_CurrentState->DeInit();
			StateManager::m_CurrentState->Deletor();

			StateManager::m_CurrentState = new T(this);
			StateManager::m_CurrentState->Init();

			return StateManager::m_CurrentState;
		}

		void Update();
		void Display();
};