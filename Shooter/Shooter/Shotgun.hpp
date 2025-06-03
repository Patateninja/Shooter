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

		inline const float GetWalkSpeedMultiplier() const { return this->m_Stock.GetWalkMod(); }
		inline const float GetAccuracyMultiplier() const { return this->m_Stock.GetAccuracyMod() * this->m_GripAttachement.GetAccuracyMod(); }
		inline const float GetRoFMultiplier() const { return this->m_GripAttachement.GetROFMod(); }
		inline const float GetRecoilModifier() const { return this->m_GripAttachement.GetRecoilMod() * this->m_Stock.GetRecoilMod(); }
		inline const std::vector<std::unique_ptr<Shell>>& GetShells() const { return this->m_Magazine; }
		inline const bool Empty() const { return this->m_Magazine.empty(); }
		inline const bool Full() const { return this->m_Magazine.size() >= this->m_DefaultCapacity + this->m_MagazineAttachement.GetCapacity(); }
		
		void Modify(Muzzle& _muzzle, Grip& _grip, Magazine& _magazine, Stock& _stock);

		void Load(int _input);
		void Shoot(sf::Vector2f& _playerPos, sf::Vector2f& _playerVel, float _playerAngle, Window& _window);
		void EmptyMagazine();

		void ReduceRecoil();

		void DisplayMagazine(Window& _window);

};