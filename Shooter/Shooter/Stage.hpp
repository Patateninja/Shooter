#pragma once
#include "Player.hpp"
#include "Crate.hpp"
#include "Camera.hpp"
#include "BonusPopUp.hpp"

class Stage
{
	private :
		sf::RenderTexture m_MapTexture;
		TileMap m_TileMap = TileMap(sf::Vector2i(40, 40));
		sf::Sprite m_MapSprite;
		EnemyList m_EnemyList;
		Crate* m_Crate = nullptr;
		int m_Num = 0;
		bool m_ReadyToMoveOn = false;
		bool m_GiveCoffee = false;
		bool m_GiveBMG = false;
		bool m_GiveVest = false;

	public :
		Stage() = default;
		Stage(int _num);
		~Stage();

		inline EnemyList& GetEnemies() { return this->m_EnemyList; }
		inline TileMap& GetMap() { return this->m_TileMap; }
		inline const int GetNum() const { return this->m_Num; }
		inline const bool GetMoveOn() const { return this->m_ReadyToMoveOn; }

		inline void SetNum(int _num) { this->m_Num = _num; };

		void GenerateMap(Player& _player);
		void SpawnEnemies();

		void Init(Player& _player);
		void Update(Player& _playerpos, Camera& _cam, BonusPopUp*& _popUp, Window& _window);
		void Display(Window& _window);
};