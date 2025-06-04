#pragma once
#include "Window.hpp"
#include "Shotgun.hpp"
#include "Button.hpp"

class LoadMenu
{
	private :
		Button m_BirdShot = Button("", sf::Vector2f(), sf::Vector2f(110.f, 50.f), &RscMana::Get<sf::Texture>("Placeholder"));
		Button m_BuckShot = Button("", sf::Vector2f(), sf::Vector2f(110.f, 50.f),  &RscMana::Get<sf::Texture>("Red_Shell"));
		Button m_DragonBreath = Button("", sf::Vector2f(), sf::Vector2f(110.f, 50.f), &RscMana::Get<sf::Texture>("Placeholder"));
		Button m_Slug = Button("", sf::Vector2f(), sf::Vector2f(110.f, 50.f),  &RscMana::Get<sf::Texture>("Placeholder"));
		sf::RectangleShape m_Rect = sf::RectangleShape(sf::Vector2f(130.f, 250.f));
		float m_InputTimer = 0.f;

	public :
		LoadMenu() = default;
		~LoadMenu() = default;

		void Update(int& _buckshot, int& _dragonbreath, int& _slug, bool _bmg, Window& _window, Shotgun& _shogtun);
		void Display(Window& _window);
};