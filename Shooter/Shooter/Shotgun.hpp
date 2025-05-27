#pragma once
#include "ResourceManager.hpp"
#include "Attachment.hpp"
#include "Shell.hpp"

class Shotgun
{
	private :
		sf::RectangleShape m_Renderer;
		Muzzle m_MuzzleAttachement;
		Grip m_GripAttachement;
		Stock m_Stock;
		Magazine m_MagazineAttachement;
		std::vector<std::unique_ptr<Shell>> m_Magazine;
		float m_Recoil = 1.f;
		int m_DefaultCapacity = 4;

	public :
		Shotgun() = default;
		~Shotgun();

		inline const float GetWalkSpeedMultiplier() { return this->m_Stock.GetWalkMod(); }
		inline const float GetAimSpeedMultiplier() { return this->m_Stock.GetAimMod() * this->m_GripAttachement.GetAimMod(); }
		inline const float GetRoFMultiplier() { return this->m_GripAttachement.GetROFMod(); }
		inline const float GetRecoilModifier() { return this->m_GripAttachement.GetRecoilMod() * this->m_Stock.GetRecoilMod(); }
		inline const std::vector<std::unique_ptr<Shell>>& GetShells() { return this->m_Magazine; }
		inline const bool Empty() { return this->m_Magazine.empty(); }
		inline const bool Full() { return this->m_Magazine.size() >= this->m_DefaultCapacity + this->m_MagazineAttachement.GetCapacity(); }
		
		void Modify(Muzzle& _muzzle, Grip& _grip, Magazine& _magazine, Stock& _stock);

		void Load(int _input);
		void Shoot(sf::Vector2f& _playerPos, sf::Vector2f& _playerVel, Window& _window);
		void EmptyMagazine();

		void ReduceRecoil();

		void DisplayMagazine(Window& _window);

};