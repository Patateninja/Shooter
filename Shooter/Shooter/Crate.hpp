#pragma once
#include "Player.hpp"
#include "Tile.hpp"
#include "BonusPopUp.hpp"

typedef enum Boost
{
	MEDKIT,
	AMMOBOX,
	XP,
} Boost;

typedef enum Bonus
{
	COFFEE,
	VEST,
	BMG50,
} Bonus;

class Crate
{
	protected :
		sf::Text m_Text = sf::Text("E",RscMana::Get<sf::Font>("Mono"));
		sf::RectangleShape m_Rect = sf::RectangleShape(sf::Vector2f(float(Tile::GetSize()), float(Tile::GetSize())));
		sf::Vector2f m_Pos;
		bool m_PlayerClose = false;
		bool m_Opened = false;

	public :
		Crate() = default;
		~Crate() = default;

		virtual void Delete() = 0;

		virtual void Update(Player& _player, BonusPopUp*& _popUp) = 0;
		void Display(Window& _window);
};

class BoostCrate : public Crate
{
	private :
		Boost m_Boost;

	public :
		BoostCrate() = default;
		BoostCrate(sf::Vector2f _pos, bool _canBeHealth, bool _canBeAmmo);
		~BoostCrate() = default;

		void Update(Player& _player, BonusPopUp*& _popUp) override;

		void Delete() override;
};

class BonusCrate : public Crate
{
	private :
		Bonus m_Bonus;

	public:
		BonusCrate() = default;
		BonusCrate(sf::Vector2f _pos);
		~BonusCrate() = default;

		void Update(Player& _player, BonusPopUp*& _popUp) override;

		void Delete() override;
};