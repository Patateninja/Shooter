#pragma once
#include "ReloadButton.hpp"
#include "Player.hpp"

class ReloadMenu
{
	private :
		ReloadButton m_BirdShot = ReloadButton("", "A small cartrige with not a lot of fire power but a lot of lead.\nLuckly you have plenty of those.", sf::Vector2f(), sf::Vector2f(140.f, 50.f), &RscMana::Get<sf::Texture>("Bird"));
		ReloadButton m_BuckShot = ReloadButton("", "Launch a volley of pellets at whatever you're aiming for.\nPretty efficient at close range.", sf::Vector2f(), sf::Vector2f(140.f, 50.f),  &RscMana::Get<sf::Texture>("Buck"));
		ReloadButton m_DragonBreath = ReloadButton("", "A special ammunition, spewing firery projectiles, setting everything afflame.\nSet ennemies on fire, dealing damage over time.", sf::Vector2f(), sf::Vector2f(140.f, 50.f), &RscMana::Get<sf::Texture>("Dragon"));
		ReloadButton m_Slug = ReloadButton("", "An unique but powefull chunck of metal, shreading everything in its path\nPierce trough flesh & steel.", sf::Vector2f(), sf::Vector2f(140.f, 50.f),  &RscMana::Get<sf::Texture>("Slug"));
		Button m_Ready = Button("", sf::Vector2f(), sf::Vector2f(140.f, 50.f), &RscMana::Get<sf::Texture>("ReadyButton"));
		sf::RectangleShape m_Rect = sf::RectangleShape(sf::Vector2f(160.f, 250.f));
		float m_InputTimer = 1.f;
		bool m_BMG = false;
		bool m_ShotgunHasAmmo = false;

	public :
		ReloadMenu() = default;
		~ReloadMenu() = default;

		void SwitchButtonMode(bool _bmg);

		void Update(Player& _player, EnemyList& _enemyList, Window& _window);
		void Display(Window& _window);
};