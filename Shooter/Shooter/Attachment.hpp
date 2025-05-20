#pragma once
#include "Window.hpp"

class Attachment
{
	protected:
		std::string m_Name = "Default";
		int m_UnlockLevel = 0;
	public :
		Attachment() = default;
		~Attachment() = default;
};

class Muzzle : public Attachment
{
	private :
		float m_SpreadModifier;
		float m_VelocityModifier;
		float m_RangeModifier;
	public :
		Muzzle();
		Muzzle(std::string _name, int _level, float _spread, float _velocity, float _range);
		~Muzzle() = default;

		inline float GetSpreadMod() { return this->m_SpreadModifier; }
		inline float GetVelocityMod() { return this->m_VelocityModifier; }
		inline float GetRangeMod() { return this->m_RangeModifier; }
};

class Magazine : public Attachment
{
	private :
		int m_Capacity;
	public :
		Magazine();
		Magazine(std::string _name, int _level, int _capacity);
		~Magazine() = default;

		inline int GetCapacity() { return this->m_Capacity; }
};

class Grip : public Attachment
{
	private :
		float m_AimSpeedModifier;
		float m_RecoilModifier;
		float m_RateOfFireModifier;

	public :
		Grip();
		Grip(std::string _name, int _level, float _aim, float _recoil, float _rof);
		~Grip() = default;

		inline float GetAimMod() { return this->m_AimSpeedModifier; }
		inline float GetRecoilMod() { return this->m_RecoilModifier; }
		inline float GetROFMod() { return this->m_RateOfFireModifier; }
};

class Stock : public Attachment
{
	private :
		float m_AimSpeedModifier;
		float m_RecoilModifier;
		float m_WalkSpeedModifier;
	public  :
		Stock();
		Stock(std::string _name, int _level, float _aim, float _recoil, float _walk);
		~Stock() = default;

		inline float GetAimMod() { return this->m_AimSpeedModifier; }
		inline float GetRecoilMod() { return this->m_RecoilModifier; }
		inline float GetWalkMod() { return this->m_WalkSpeedModifier; }
};