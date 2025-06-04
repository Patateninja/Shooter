#pragma once
#include "Button.hpp"
#include "Player.hpp"

class ReloadMenu
{
	private :
		Button m_BirdShot = Button("", sf::Vector2f(), sf::Vector2f(110.f, 50.f), &RscMana::Get<sf::Texture>("Placeholder"));
		Button m_BuckShot = Button("", sf::Vector2f(), sf::Vector2f(110.f, 50.f),  &RscMana::Get<sf::Texture>("Red_Shell"));
		Button m_DragonBreath = Button("", sf::Vector2f(), sf::Vector2f(110.f, 50.f), &RscMana::Get<sf::Texture>("Placeholder"));
		Button m_Slug = Button("", sf::Vector2f(), sf::Vector2f(110.f, 50.f),  &RscMana::Get<sf::Texture>("Placeholder"));
		sf::RectangleShape m_Rect = sf::RectangleShape(sf::Vector2f(130.f, 250.f));
		float m_InputTimer = 1.f;

	public :
		ReloadMenu() = default;
		~ReloadMenu() = default;

		void Update(Player& _player, Window& _window);
		void Display(Window& _window);
};