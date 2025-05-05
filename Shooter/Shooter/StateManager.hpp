#pragma once
#include "Window.hpp"
#include "State.hpp"

class StateManager
{
	private:
		Window m_Window;
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
			StateManager::m_CurrentState;

			StateManager::m_CurrentState = new T(this);
			StateManager::m_CurrentState->Init();

			return StateManager::m_CurrentState;
		}

		Window& GetWindow() { return this->m_Window; };
		bool WindowIsOpen() { return StateManager::m_Window.IsOpen(); };

		void ClearWindow();
		void Draw(sf::Drawable& _toDraw);
		void DisplayWindow();

		void Update();
		void Display();
};