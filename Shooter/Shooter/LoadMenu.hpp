#pragma once
#include "Window.hpp"
#include "Shotgun.hpp"
#include "Button.hpp"

class LoadMenu
{
	private :
		Button m_BirdShot = Button("", sf::Vector2f(10.f, 40.f), sf::Vector2f(110.f, 50.f), &RscMana::Get<sf::Texture>("Placeholder"));
		Button m_BuckShot = Button("", sf::Vector2f(10.f, 100.f), sf::Vector2f(110.f, 50.f),  &RscMana::Get<sf::Texture>("Placeholder"));
		Button m_DragonBreath = Button("", sf::Vector2f(10.f, 160.f), sf::Vector2f(110.f, 50.f), &RscMana::Get<sf::Texture>("Placeholder"));
		Button m_Slug = Button("", sf::Vector2f(10.f, 220.f), sf::Vector2f(110.f, 50.f),  &RscMana::Get<sf::Texture>("Placeholder"));
		sf::Text m_Text = sf::Text("",RscMana::Get<sf::Font>("Mono"));
		sf::RectangleShape m_Rect = sf::RectangleShape(sf::Vector2f(250.f, 260.f));
		sf::String infinite = L"\u221E"; //Either put on the texture or move to an other file
		float m_InputTimer = 0.f;

	public :
		LoadMenu() = default;
		~LoadMenu() = default;

		void Update(int& _buckshot, int& _dragonbreath, int& _slug, bool _bmg, Window& _window, Shotgun& _shogtun);
		void Display(Window& _window);
};