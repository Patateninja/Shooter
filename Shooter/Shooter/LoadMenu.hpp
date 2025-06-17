#pragma once
#include "Button.hpp"
#include "Player.hpp"

class ReloadMenu
{
	private :
		Button m_BirdShot = Button("", sf::Vector2f(), sf::Vector2f(140.f, 50.f), &RscMana::Get<sf::Texture>("Bird"));
		Button m_BuckShot = Button("", sf::Vector2f(), sf::Vector2f(140.f, 50.f),  &RscMana::Get<sf::Texture>("Buck"));
		Button m_DragonBreath = Button("", sf::Vector2f(), sf::Vector2f(140.f, 50.f), &RscMana::Get<sf::Texture>("Dragon"));
		Button m_Slug = Button("", sf::Vector2f(), sf::Vector2f(140.f, 50.f),  &RscMana::Get<sf::Texture>("Slug"));
		sf::RectangleShape m_Rect = sf::RectangleShape(sf::Vector2f(160.f, 250.f));
		float m_InputTimer = 1.f;

	public :
		ReloadMenu() = default;
		~ReloadMenu() = default;

		void Update(Player& _player, Window& _window);
		void Display(Window& _window);
};