#pragma once
#include "Window.hpp"
#include "Player.hpp"
#include "Tile.hpp"
//#include "Bonus.hpp"
//#include "Boost.hpp"

class Boost;
class Bonus;

class Crate
{
	protected :
		sf::RectangleShape m_Rect = sf::RectangleShape(sf::Vector2f(float(Tile::GetSize()), float(Tile::GetSize())));
		sf::Vector2f m_Pos;

	public :
		Crate() = default;
		~Crate() = default;

		virtual void Delete() = 0;

		virtual void Update(Player& _player) = 0;
		void Display(Window& _window);
};

class BoostCrate : public Crate
{
	private :
		std::unique_ptr<Boost> m_Boost = nullptr;

	public :
		BoostCrate() = default;
		BoostCrate(sf::Vector2f _pos, bool _canBeHealth, bool _canBeAmmo);
		BoostCrate() = default;

		void Update(Player& _player) override;
};

class BonusCrate : public Crate
{
	private:
		std::unique_ptr<Boost> m_Boost = nullptr;

	public:
		BonusCrate() = default;
		BonusCrate(sf::Vector2f _pos);
		BonusCrate() = default;

		void Update(Player& _player) override;
};