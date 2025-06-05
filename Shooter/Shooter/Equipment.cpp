#include "Equipment.hpp"

//////////////////////////////////////////////////

Armor::Armor()
{
	this->m_Name = "Default";
	this->m_UnlockLevel = 0;

	this->m_BonusLife = 0;
	this->m_WalkingSpeedModifier = 1.f;
}

Armor::Armor(std::string _name, int _level, int _life, float _walking)
{
	this->m_Name = _name;
	this->m_UnlockLevel = _level;

	this->m_BonusLife = _life;
	this->m_WalkingSpeedModifier = _walking;
}

Armor::Armor(const Armor& _armor)
{
	this->m_Name = _armor.m_Name;
	this->m_UnlockLevel = _armor.m_UnlockLevel;

	this->m_BonusLife = _armor.m_BonusLife;
	this->m_WalkingSpeedModifier = _armor.m_WalkingSpeedModifier;
}

//////////////////////////////////////////////////

AmmoStash::AmmoStash()
{
	this->m_Name = "Default";
	this->m_UnlockLevel = 0;

	this->m_Capacity = 0;
}

AmmoStash::AmmoStash(std::string _name, int _level, int _capacity)
{
	this->m_Name = _name;
	this->m_UnlockLevel = _level;

	this->m_Capacity = _capacity;
}

AmmoStash::AmmoStash(const AmmoStash& _magazine)
{
	this->m_Name = _magazine.m_Name;
	this->m_UnlockLevel = _magazine.m_UnlockLevel;

	this->m_Capacity = _magazine.m_Capacity;
}

//////////////////////////////////////////////////