#pragma once
#include "Window.hpp"
#include "Tile.hpp"
#include "Enemy.hpp"
#include "Player.hpp"

class Stage
{
	private :
		sf::RenderTexture m_MapTexture;
		TileMap m_TileMap;
		sf::Sprite m_MapSprite;
		EnemyList m_EnemyList;
		int m_Num = 0;
	public :
		Stage() = default;
		Stage(int _num);
		~Stage() = default;

		inline EnemyList& GetEnemies() { return this->m_EnemyList; };
		inline TileMap& GetMap() { return this->m_TileMap; };
		inline int GetNum() { return this->m_Num; };
		inline void SetNum(int _num) { this->m_Num = _num; };

		void GenerateMap();
		void SpawnEnemies();

		void Init();
		void Update(Player& _playerpos);
		void Display(Window& _window);
};