#include "Attachment.hpp"

//////////////////////////////////////////////////

Muzzle::Muzzle(std::string _name, int _level, float _spread, float _velocity, float _range)
{
	this->m_Name = _name;
	this->m_UnlockLevel = _level;

	this->m_SpreadModifier = _spread;
	this->m_VelocityModifier = _velocity;
	this->m_RangeModifier = _range;
}

Muzzle::Muzzle(const Muzzle& _muzzle)
{
	this->m_Name = _muzzle.m_Name;
	this->m_UnlockLevel = _muzzle.m_UnlockLevel;

	this->m_RangeModifier = _muzzle.m_RangeModifier;
	this->m_SpreadModifier = _muzzle.m_SpreadModifier;
	this->m_VelocityModifier = _muzzle.m_VelocityModifier;
}

//////////////////////////////////////////////////

Magazine::Magazine(std::string _name, int _level, int _capacity)
{
	this->m_Name = _name;
	this->m_UnlockLevel = _level;

	this->m_Capacity = _capacity;
}

Magazine::Magazine(const Magazine& _magazine)
{
	this->m_Name = _magazine.m_Name;
	this->m_UnlockLevel = _magazine.m_UnlockLevel;

	this->m_Capacity = _magazine.m_Capacity;
}

//////////////////////////////////////////////////

Grip::Grip(std::string _name, int _level, float _accuracy, float _recoil, float _rof)
{
	this->m_Name = _name;
	this->m_UnlockLevel = _level;

	this->m_AccuracyModifier = _accuracy;
	this->m_RecoilModifier = _recoil;
	this->m_RateOfFireModifier = _rof;
}

Grip::Grip(const Grip& _grip)
{
	this->m_Name = _grip.m_Name;
	this->m_UnlockLevel = _grip.m_UnlockLevel;

	this->m_AccuracyModifier = _grip.m_AccuracyModifier;
	this->m_RecoilModifier = _grip.m_RecoilModifier;
	this->m_RateOfFireModifier = _grip.m_RateOfFireModifier;
}

//////////////////////////////////////////////////

Stock::Stock(std::string _name, int _level, float _accuracy, float _recoil, float _walk)
{
	this->m_Name = _name;
	this->m_UnlockLevel = _level;

	this->m_AccuracyModifier = _accuracy;
	this->m_RecoilModifier = _recoil;
	this->m_WalkSpeedModifier = _walk;
}

Stock::Stock(const Stock& _stock)
{
	this->m_Name = _stock.m_Name;
	this->m_UnlockLevel = _stock.m_UnlockLevel;

	this->m_AccuracyModifier = _stock.m_AccuracyModifier;
	this->m_RecoilModifier = _stock.m_RecoilModifier;
	this->m_WalkSpeedModifier = _stock.m_WalkSpeedModifier;
}

//////////////////////////////////////////////////