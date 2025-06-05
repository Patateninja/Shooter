#include "Save.hpp"

namespace SaveSystem
{
	void Save(std::string _filename, int& _xp, Muzzle& _muzzle, Grip& _grip, Stock& _stock, Magazine& _magazine, Armor& _armor, AmmoStash& _ammoStash)
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

		file.close();
	}

	void Load(std::string _filename, int& _xp, Muzzle& _muzzle, Grip& _grip, Stock& _stock, Magazine& _magazine, Armor& _armor, AmmoStash& _ammoStash)
	{
		std::ifstream file;
		file.open("..\\Save\\" + _filename);

		std::string xp;
		std::getline(file >> std::ws, xp);
		_xp = std::stoi(xp);

		std::string name;

		#pragma region Muzzle
		std::getline(file >> std::ws,name);
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
		std::getline(file >> std::ws,name);
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
		std::getline(file >> std::ws,name);
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
			_stock = Stock("No Stock", 26, 0.5f, 1.5f, 1.5f);
		}
		else
		{
			_stock = Stock("Default Stock", 0, 1.f, 1.f, 1.f);
		}
		#pragma endregion

		#pragma region Magazine
		std::getline(file >> std::ws,name);
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
		std::getline(file >> std::ws,name);
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
			_armor = Armor("Recon Armor", 16, 3, 1.25f);
		}
		else if (name == "Jugernaut Armor")
		{
			_armor = Armor("Jugernaut Armor", 32, 6, 0.5f);
		}
		else
		{
			_armor = Armor("None", 0, 0, 1.f);
		}
		#pragma endregion

		#pragma region AmmoStash
		std::getline(file >> std::ws,name);
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

		file.close();
	}
}