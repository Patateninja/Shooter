#pragma once
#include "Window.hpp"
#include "Button.hpp"

class StateManager;

class PauseMenu
{
	private :
		Button m_Resume = Button("Resume", sf::Vector2f(), sf::Vector2f(400.f, 100.f), &RscMana::Get<sf::Texture>("Placeholder"));
		Button m_ToShop = Button("Back To Shop", sf::Vector2f(), sf::Vector2f(400.f, 100.f), &RscMana::Get<sf::Texture>("ShopButton"));
		Button m_ToMenu = Button("Quit to Main Menu", sf::Vector2f(), sf::Vector2f(400.f, 100.f), &RscMana::Get<sf::Texture>("MenuButton"));
		Button m_ToDesktop = Button("Quit To Desktop", sf::Vector2f(), sf::Vector2f(400.f, 100.f), &RscMana::Get<sf::Texture>("Placeholder"));

	public :
		PauseMenu() = default;
		~PauseMenu() = default;

		void Update(Window& _window, bool& _paused, StateManager& _stateManager);
		void Display(Window& _window);
};