#pragma once
#include "Window.hpp"

class Equipment
{
	protected:
		std::string m_Name = "Default";
		int m_UnlockLevel = 0;
	public:
		Equipment() = default;
		~Equipment() = default;

		virtual void foo() {};

		inline std::string& GetName() { return this->m_Name; }
		inline const int GetUnlockLevel() const { return this->m_UnlockLevel; }
};

class Armor : public Equipment
{
	private:
		int m_BonusLife;
		float m_WalkingSpeedModifier;
	public:
		Armor();
		Armor(std::string _name, int _level, int _life, float _walking);
		Armor(const Armor& _muzzle);
		~Armor() = default;

		inline const int GetLife() const { return this->m_BonusLife; }
		inline const float GetWalkSpeedMod() const { return this->m_WalkingSpeedModifier; }
};

class AmmoStash : public Equipment
{
	private:
		int m_Capacity;
	public:
		AmmoStash();
		AmmoStash(std::string _name, int _level, int _capacity);
		AmmoStash(const AmmoStash& _magazine);
		~AmmoStash() = default;

		inline const int GetCapacity() const { return this->m_Capacity; }
};

