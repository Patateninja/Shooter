#pragma once
#include "Attachment.hpp"
#include "Equipment.hpp"
#include <fstream>

namespace SaveSystem
{
	void Save(std::string _filename, int& _xp, Muzzle& _muzzle, Grip& _grip, Stock& _Stock, Magazine& _magazine, Armor& _armor, AmmoStash& _ammoStash, int& _sfxVolume, int& _bgmVolume, int& _bestStage);
	void Load(std::string _filename, int& _xp, Muzzle& _muzzle, Grip& _grip, Stock& _Stock, Magazine& _magazine, Armor& _armor, AmmoStash& _ammoStash, int& _sfxVolume, int& _bgmVolume, int& _bestStage);
}