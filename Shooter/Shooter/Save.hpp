#pragma once
#include "Attachment.hpp"
#include "Equipment.hpp"
#include <fstream>
#include <string>

namespace SaveSystem
{
	void Save(std::string _filename, int& _xp, Muzzle& _muzzle, Grip& _grip, Stock& _Stock, Magazine& _magazine, Armor& _armor, AmmoStash& _ammoStash);
	void Load(std::string _filename, int& _xp, Muzzle& _muzzle, Grip& _grip, Stock& _Stock, Magazine& _magazine, Armor& _armor, AmmoStash& _ammoStash);
}