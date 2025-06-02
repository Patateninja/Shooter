#pragma once
#include "Player.hpp"
#include "Crate.hpp"
#include "Camera.hpp"
#include "BonusPopUp.hpp"

class Stage
{
	private :
		sf::RenderTexture m_MapTexture;
		TileMap m_TileMap;
		sf::Sprite m_MapSprite;
		EnemyList m_EnemyList;
		Crate* m_Crate = nullptr;
		int m_Num = 0;
		bool m_ReadyToMoveOn = false;

	public :
		Stage() = default;
		Stage(int _num);
		~Stage() = default;

		inline EnemyList& GetEnemies() { return this->m_EnemyList; }
		inline TileMap& GetMap() { return this->m_TileMap; }
		inline const int GetNum() const { return this->m_Num; }
		inline const bool GetMoveOn() const { return this->m_ReadyToMoveOn; }

		inline void SetNum(int _num) { this->m_Num = _num; };

		void GenerateMap();
		void SpawnEnemies();

		void Init();
		void Update(Player& _playerpos, Camera& _cam, BonusPopUp*& _popUp, Window& _window);
		void Display(Window& _window);
};