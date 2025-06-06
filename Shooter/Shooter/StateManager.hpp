#pragma once
#include "Window.hpp"
#include "State.hpp"
#include "Save.hpp"

class StateManager
{
	private :
		Window m_Window;
		State* m_CurrentState;
		float m_InputTimer;
	public :
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

		Window& GetWindow() { return this->m_Window; };
		bool WindowIsOpen() { return this->m_Window.IsOpen(); };
		bool WindowHasFocus() { return this->m_Window.HasFocus(); };

		void ClearWindow();
		void Draw(const sf::Drawable& _toDraw);
		void DisplayWindow();

		void Update();
		void Display();
};