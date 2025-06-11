#include "Save.hpp"

namespace SaveSystem
{
	void Save(std::string _filename, int& _xp, Muzzle& _muzzle, Grip& _grip, Stock& _stock, Magazine& _magazine, Armor& _armor, AmmoStash& _ammoStash, int& _sfxVolume, int& _bgmVolume)
	{
		std::ofstream file;
		file.open("..\\Save\\" + _filename);

		file << std::to_string(_xp) + '\n';

		file << _muzzle.GetName() + '\n';
		file << _grip.GetName() + '\n';
		file << _stock.GetName() + '\n';
		file << _magazine.GetName() + '\n';

		file << _armor.GetName() + '\n';
		file << _ammoStash.GetName() + '\n';

		file << std::to_string(_sfxVolume) + '\n';
		file << std::to_string(_bgmVolume) + '\n';

		file.close();
	}

	void Load(std::string _filename, int& _xp, Muzzle& _muzzle, Grip& _grip, Stock& _stock, Magazine& _magazine, Armor& _armor, AmmoStash& _ammoStash, int& _sfxVolume, int& _bgmVolume)
	{
		std::ifstream file;
		file.open("..\\Save\\" + _filename);

		if (file.is_open())
		{
			std::string xp;
			std::getline(file >> std::ws, xp);
			try
			{
				_xp = std::stoi(xp);
			}
			catch (std::exception)
			{
				_xp = 0;
			}

			std::string name;

			#pragma region Muzzle
			std::getline(file >> std::ws, name);
			if (name == "Choke Muzzle")
			{
				_muzzle = Muzzle("Choke Muzzle", 3, 0.5f, 1.3f, 1.2f);
			}
			else if (name == "Muzzle Brake")
			{
				_muzzle = Muzzle("Muzzle Brake", 10, 0.7f, 1.2f, 1.5f);
			}
			else if (name == "Sawed Off")
			{
				_muzzle = Muzzle("Sawed Off", 20, 2.f, 1.2f, 0.5f);
			}
			else
			{
				_muzzle = Muzzle("Default Muzzle", 0, 1.f, 1.f, 1.f);
			}
			#pragma endregion

			#pragma region Grip
			std::getline(file >> std::ws, name);
			if (name == "Vertical Grip")
			{
				_grip = Grip("Vertical Grip", 4, 1.5f, 0.85f, 1.1f);
			}
			else if (name == "Horizontal Grip")
			{
				_grip = Grip("Horizontal Grip", 9, 1.1f, 0.5f, 1.15f);
			}
			else if (name == "Speed Grip")
			{
				_grip = Grip("Speed Grip", 18, 1.15f, 0.9f, 1.5f);
			}
			else
			{
				_grip = Grip("Default Grip", 0, 1.f, 1.f, 1.f);
			}
			#pragma endregion

			#pragma region Stock
			std::getline(file >> std::ws, name);
			if (name == "Light Recon Stock")
			{
				_stock = Stock("Light Recon Stock", 5, 1.25f, 0.85f, 1.1f);
			}
			else if (name == "Heavy Assault Stock")
			{
				_stock = Stock("Heavy Assault Stock", 8, 0.9f, 0.5f, 0.9f);
			}
			else if (name == "No Stock")
			{
				_stock = Stock("No Stock", 26, 0.5f, 1.5f, 1.3f);
			}
			else
			{
				_stock = Stock("Default Stock", 0, 1.f, 1.f, 1.f);
			}
			#pragma endregion

			#pragma region Magazine
			std::getline(file >> std::ws, name);
			if (name == "6 Shell Tube")
			{
				_magazine = Magazine("6 Shell Tube", 6, 2);
			}
			else if (name == "8 Shell Tube")
			{
				_magazine = Magazine("8 Shell Tube", 14, 4);
			}
			else if (name == "12 Shell Drum")
			{
				_magazine = Magazine("12 Shell Drum", 29, 8);
			}
			else
			{
				_magazine = Magazine("Default Magazine", 0, 0);
			}
			#pragma endregion

			#pragma region Armor
			std::getline(file >> std::ws, name);
			if (name == "Flak Vest")
			{
				_armor = Armor("Flak Vest", 2, 1, 1.f);
			}
			else if (name == "Marine Armor")
			{
				_armor = Armor("Marine Armor", 7, 2, 1.f);
			}
			else if (name == "Recon Armor")
			{
				_armor = Armor("Recon Armor", 16, 3, 1.2f);
			}
			else if (name == "Jugernaut Armor")
			{
				_armor = Armor("Jugernaut Armor", 32, 8, 0.7f);
			}
			else
			{
				_armor = Armor("None", 0, 0, 1.f);
			}
			#pragma endregion

			#pragma region AmmoStash
			std::getline(file >> std::ws, name);
			if (name == "Ammo Belt")
			{
				_ammoStash = AmmoStash("Ammo Belt", 1, 5);
			}
			else if (name == "Bandolier")
			{
				_ammoStash = AmmoStash("Bandolier", 12, 10);
			}
			else if (name == "Satchel")
			{
				_ammoStash = AmmoStash("Satchel", 23, 20);
			}
			else if (name == "Tactical Backpack")
			{
				_ammoStash = AmmoStash("Tactical Backpack", 35, 40);
			}
			else
			{
				_ammoStash = AmmoStash("Ammo Pouch", 0, 0);
			}
			#pragma endregion

			std::string volume;
			std::getline(file >> std::ws, volume);
			try
			{
				_sfxVolume = std::stoi(volume);
			}
			catch (std::exception)
			{
				_sfxVolume = 100;
			}

			std::getline(file >> std::ws, volume);
			try
			{
				_bgmVolume = std::stoi(volume);
			}
			catch (std::exception)
			{
				_bgmVolume = 100;
			}
		}
		else
		{
			_xp = 0;
			_muzzle = Muzzle("Default Muzzle", 0, 1.f, 1.f, 1.f);
			_grip = Grip("Default Grip", 0, 1.f, 1.f, 1.f);
			_stock = Stock("Default Stock", 0, 1.f, 1.f, 1.f);
			_magazine = Magazine("Default Magazine", 0, 0);
			_armor = Armor("None", 0, 0, 1.f);
			_ammoStash = AmmoStash("Ammo Pouch", 0, 0);
			_sfxVolume = 100;
			_bgmVolume = 100;
		}

		file.close();
	}
}