#pragma once
#include "Window.hpp"
#include "Button.hpp"

class StateManager;

class PauseMenu
{
	private :
		Button m_Resume = Button("Resume", sf::Vector2f(), sf::Vector2f(400.f, 100.f), &RscMana::Get<sf::Texture>("Placeholder"));
		Button m_ToShop = Button("", sf::Vector2f(), sf::Vector2f(400.f, 100.f), &RscMana::Get<sf::Texture>("ShopButton"));
		Button m_ToMenu = Button("", sf::Vector2f(), sf::Vector2f(400.f, 100.f), &RscMana::Get<sf::Texture>("MenuButton"));
		Button m_ToDesktop = Button("", sf::Vector2f(), sf::Vector2f(400.f, 100.f), &RscMana::Get<sf::Texture>("ExitButton"));

	public :
		PauseMenu() = default;
		~PauseMenu() = default;

		void Update(Window& _window, bool& _paused, StateManager& _stateManager);
		void Display(Window& _window);
};