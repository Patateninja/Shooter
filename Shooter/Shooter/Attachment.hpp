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

		virtual void foo() {};

		inline const std::string& GetName() const { return this->m_Name; }
		inline const int GetUnlockLevel() const { return this->m_UnlockLevel; }
};

class Muzzle : public Attachment
{
	private :
		float m_SpreadModifier = 1.f;
		float m_VelocityModifier = 1.f;
		float m_RangeModifier = 1.f;

	public :
		Muzzle() = default;
		Muzzle(std::string _name, int _level, float _spread, float _velocity, float _range);
		Muzzle(const Muzzle& _muzzle);
		~Muzzle() = default;

		inline const float GetSpreadMod() const { return this->m_SpreadModifier; }
		inline const float GetVelocityMod() const { return this->m_VelocityModifier; }
		inline const float GetRangeMod() const { return this->m_RangeModifier; }
};

class Magazine : public Attachment
{
	private :
		int m_Capacity = 0;

	public :
		Magazine() = default;
		Magazine(std::string _name, int _level, int _capacity);
		Magazine(const Magazine& _magazine);
		~Magazine() = default;

		inline const int GetCapacity() const { return this->m_Capacity; }
};

class Grip : public Attachment
{
	private :
		float m_AccuracyModifier = 1.f;
		float m_RecoilModifier = 1.f;
		float m_RateOfFireModifier = 1.f;

	public :
		Grip() = default;
		Grip(std::string _name, int _level, float _accuracy, float _recoil, float _rof);
		Grip(const Grip& _grip);
		~Grip() = default;

		inline const float GetAccuracyMod() const { return this->m_AccuracyModifier; }
		inline const float GetRecoilMod() const { return this->m_RecoilModifier; }
		inline const float GetROFMod() const { return this->m_RateOfFireModifier; }
};

class Stock : public Attachment
{
	private :
		float m_AccuracyModifier = 1.f;
		float m_RecoilModifier = 1.f;
		float m_WalkSpeedModifier = 1.f;

	public  :
		Stock() = default;
		Stock(std::string _name, int _level, float _accuracy, float _recoil, float _walk);
		Stock(const Stock& _stock);
		~Stock() = default;

		inline const float GetAccuracyMod() const { return this->m_AccuracyModifier; }
		inline const float GetRecoilMod() const { return this->m_RecoilModifier; }
		inline const float GetWalkMod() const { return this->m_WalkSpeedModifier; }
};