#pragma once
#include "ResourceManager.hpp"
#include "Attachment.hpp"
#include "Shell.hpp"

class Shotgun
{
	private :
		sf::RectangleShape m_Renderer;
		std::vector<std::unique_ptr<Shell>> m_Magazine;
		int m_DefaultCapacity;
		Muzzle m_MuzzleAttachement;
		Grip m_GripAttachement;
		Magazine m_MagazineAttachement;
		Stock m_Stock;
	public :
		Shotgun();
		~Shotgun();

		void Modify(Muzzle& _muzzle, Grip _grip, Magazine _magazine, Stock _stock);

		inline bool Empty() { return this->m_Magazine.empty(); };
		inline bool Full() { return this->m_Magazine.size() >= this->m_DefaultCapacity + this->m_MagazineAttachement.GetCapacity(); }
		inline float GetWalkSpeedMultiplier() { return this->m_Stock.GetWalkMod(); }
		inline float GetAimSpeedMultiplier() { return this->m_Stock.GetAimMod() * this->m_GripAttachement.GetAimMod(); }

		void DisplayMagazine(Window& _window);

		void Load(int _input);
		void Shoot(sf::Vector2f& _playerPos, sf::Vector2f& _playerVel, Window& _window);

		std::vector<std::unique_ptr<Shell>>& GetShells() { return this->m_Magazine; };
		void EmptyMagazine();
};