#include "Shop.hpp"

Shop::~Shop()
{
	for (AttachmentButton attachment : this->m_AttachementsList)
	{
		if (attachment.Get())
		{
			delete attachment.Get();
		}
	}
	this->m_AttachementsList.clear();
	
	for (EquipmentButton equipment : this->m_EquipmentList)
	{
		if (equipment.Get())
		{
			delete equipment.Get();
		}
	}
	this->m_EquipmentList.clear();
}

void Shop::LockItem()
{
	for (AttachmentButton& button : this->m_AttachementsList)
	{
		if (button.Get()->GetUnlockLevel() > this->m_PlayerLevel)
		{
			button.Lock();
		}
		else
		{
			button.Unlock();
		}
	}
	for (EquipmentButton& button : this->m_EquipmentList)
	{
		if (button.Get()->GetUnlockLevel() > this->m_PlayerLevel)
		{
			button.Lock();
		}
		else
		{
			button.Unlock();
		}
	}
}

void Shop::Init(int _lvl, Muzzle& _muzzle, Grip& _grip, Stock& _stock, Magazine& _magazine, Armor& _armor, AmmoStash& _ammostash)
{
	this->m_PlayerLevel = _lvl;
	this->m_Text.setFont(RscMana::Get<sf::Font>("Mono"));

	this->m_EquipedMuzzle = _muzzle;
	this->m_EquipedGrip = _grip;
	this->m_EquipedStock = _stock;
	this->m_EquipedMag = _magazine;
	this->m_EquipedArmor = _armor;
	this->m_EquipedAmmoStash = _ammostash;

	sf::Vector2f buttonsize(250.f, 75.f);

	#pragma region Muzzle
	this->AddAttachment(std::string("Default"), sf::Vector2f(10.f, 200.f), buttonsize, "Placeholder", new Muzzle("Default Muzzle", 0, 1.f, 1.f, 1.f));
	this->AddAttachment(std::string("Choke Muzzle"), sf::Vector2f(280.f, 200.f), buttonsize, "Placeholder", new Muzzle("Choke Muzzle", 3, 0.5f, 1.3f, 1.2f));
	this->AddAttachment(std::string("Muzzle Brake"), sf::Vector2f(550.f, 200.f), buttonsize, "Placeholder", new Muzzle("Muzzle Brake", 10, 0.7f, 1.2f, 1.5f));
	this->AddAttachment(std::string("Sawed Off"), sf::Vector2f(820.f, 200.f), buttonsize, "Placeholder", new Muzzle("Sawed Off", 20, 2.f, 1.2f, 0.5f));
	#pragma endregion

	#pragma region Grip
	this->AddAttachment(std::string("Default"), sf::Vector2f(10.f, 300.f), buttonsize, "Placeholder", new Grip("Default Grip", 0, 1.f, 1.f, 1.f));
	this->AddAttachment(std::string("Vertical Grip"), sf::Vector2f(280.f, 300.f), buttonsize, "Placeholder", new Grip("Vertical Grip", 4, 1.5f, 0.85f, 1.1f));
	this->AddAttachment(std::string("Horizontal Grip"), sf::Vector2f(550.f, 300.f), buttonsize, "Placeholder", new Grip("Horizontal Grip", 9, 1.1f, 0.5f, 1.15f));
	this->AddAttachment(std::string("Speed Grip"), sf::Vector2f(820.f, 300.f), buttonsize, "Placeholder", new Grip("Speed Grip", 18, 1.15f, 0.9f, 1.5f));
	#pragma endregion

	#pragma region Stock
	this->AddAttachment(std::string("Default"), sf::Vector2f(10.f, 400.f), buttonsize, "Placeholder", new Stock("Default Stock", 0, 1.f, 1.f, 1.f));
	this->AddAttachment(std::string("Light Recon Stock"), sf::Vector2f(280.f, 400.f), buttonsize, "Placeholder", new Stock("Light Recon Stock", 5, 1.25f, 0.85f, 1.1f));
	this->AddAttachment(std::string("Heavy Assault Stock"), sf::Vector2f(550.f, 400.f), buttonsize, "Placeholder", new Stock("Heavy Assault Stock", 8, 0.9f, 0.5f, 0.9f));
	this->AddAttachment(std::string("No Stock"), sf::Vector2f(820.f, 400.f), buttonsize, "Placeholder", new Stock("No Stock", 26, 0.5f, 1.5f, 1.5f));
	#pragma endregion

	#pragma region Magazine
	this->AddAttachment(std::string("Default"), sf::Vector2f(10.f, 500.f), buttonsize, "Placeholder", new Magazine("Default Magazine", 0, 0));
	this->AddAttachment(std::string("6 Shell Tube"), sf::Vector2f(280.f, 500.f), buttonsize, "Placeholder", new Magazine("6 Shell Tube", 6, 2));
	this->AddAttachment(std::string("8 Shell Tube"), sf::Vector2f(550.f, 500.f), buttonsize, "Placeholder", new Magazine("8 Shell Tube", 14, 4));
	this->AddAttachment(std::string("12 Shell Drum"), sf::Vector2f(820.f, 500.f), buttonsize, "Placeholder", new Magazine("12 Shell Drum", 29, 8));
	#pragma endregion

	#pragma region Armor
	this->AddEquipment(std::string("None"), sf::Vector2f(10.f, 650.f), buttonsize, "Placeholder", new Armor("None", 0, 0, 1.f));
	this->AddEquipment(std::string("Flak Vest"), sf::Vector2f(280.f, 650.f), buttonsize, "Placeholder", new Armor("Flak Vest", 2, 1, 1.f));
	this->AddEquipment(std::string("Marine Armor"), sf::Vector2f(550.f, 650.f), buttonsize, "Placeholder", new Armor("Marine Armor", 7, 2, 1.f));
	this->AddEquipment(std::string("Recon Armor"), sf::Vector2f(820.f, 650.f), buttonsize, "Placeholder", new Armor("Recon Armor", 16, 3, 1.25f));
	this->AddEquipment(std::string("Juggernaut Armor"), sf::Vector2f(1090.f, 650.f), buttonsize, "Placeholder", new Armor("Jugernaut Armor", 32, 6, 0.5f));
	#pragma endregion

	#pragma region AmmoStash
	this->AddEquipment(std::string("Ammo Pouch"), sf::Vector2f(10.f, 750.f), buttonsize, "Placeholder", new AmmoStash("Ammo Pouch", 0, 0));
	this->AddEquipment(std::string("Ammo Belt"), sf::Vector2f(280.f, 750.f), buttonsize, "Placeholder", new AmmoStash("Ammo Belt", 1, 5));
	this->AddEquipment(std::string("Bandolier"), sf::Vector2f(550.f, 750.f), buttonsize, "Placeholder", new AmmoStash("Bandolier", 12, 10));
	this->AddEquipment(std::string("Satchel"), sf::Vector2f(820.f, 750.f), buttonsize, "Placeholder", new AmmoStash("Satchel", 23, 20));
	this->AddEquipment(std::string("Tactical Backpack"), sf::Vector2f(1090.f, 750.f), buttonsize, "Placeholder", new AmmoStash("Tactical Backpack", 35, 40));
	#pragma endregion

	this->m_PopUpRect = sf::RectangleShape(sf::Vector2f(250.f, 120.f));
	this->m_PopUpRect.setFillColor(Color::DarkGrey);
	this->m_PopUpRect.setOutlineColor(Color::Grey);
	this->m_PopUpRect.setOutlineThickness(5.f);
	this->m_PopUpText.setFont(RscMana::Get<sf::Font>("Mono"));
	this->m_PopUpText.setCharacterSize(20);
}

template <typename T>
void Shop::AddAttachment(std::string _buttonName, sf::Vector2f _buttonPos, sf::Vector2f _buttonSize, std::string _textureName, T* _attachment)
{
	this->m_AttachementsList.push_back(AttachmentButton(_buttonName, _buttonPos, _buttonSize, &RscMana::Get<sf::Texture>(_textureName)));
	this->m_AttachementsList.back().Bind(*_attachment);
}
template<typename T>
void Shop::AddEquipment(std::string _buttonName, sf::Vector2f _buttonPos, sf::Vector2f _buttonSize, std::string _textureName, T* _equipment)
{
	this->m_EquipmentList.push_back(EquipmentButton(_buttonName, _buttonPos, _buttonSize, &RscMana::Get<sf::Texture>(_textureName)));
	this->m_EquipmentList.back().Bind(*_equipment);
}

void Shop::Update(Window& _window)
{
	this->LockItem(); //Move to Init after debug

	this->m_PopUp = false;

	for (AttachmentButton& button : this->m_AttachementsList)
	{
		std::string currentName = button.Get()->GetName();
		if (currentName != this->m_EquipedGrip.GetName() && currentName != this->m_EquipedMag.GetName() && currentName != this->m_EquipedMuzzle.GetName() && currentName != this->m_EquipedStock.GetName())
		{
			button.SetActive(false);
		}
		else
		{
			button.SetActive(true);
		}

		/// Temp ///
		if (this->m_EquipedMuzzle.GetUnlockLevel() > this->m_PlayerLevel)
		{
			this->m_EquipedMuzzle = Muzzle("Default Muzzle", 0, 1.f, 1.f, 1.f);
		}
		if (this->m_EquipedGrip.GetUnlockLevel() > this->m_PlayerLevel)
		{
			this->m_EquipedGrip = Grip("Default Grip", 0, 1.f, 1.f, 1.f);
		}
		if (this->m_EquipedStock.GetUnlockLevel() > this->m_PlayerLevel)
		{
			this->m_EquipedStock = Stock("Default Stock", 0, 1.f, 1.f, 1.f);
		}
		if (this->m_EquipedMag.GetUnlockLevel() > this->m_PlayerLevel)
		{
			this->m_EquipedMag = Magazine("Default Magazine", 0, 0);
		}
		////////////

		if (button.Update(_window, button.Get()->GetUnlockLevel()))
		{
			if (dynamic_cast<Muzzle*>(button.Get()))
			{
				this->m_EquipedMuzzle = *dynamic_cast<Muzzle*>(button.Get());
			}
			else if (dynamic_cast<Grip*>(button.Get()))
			{
				this->m_EquipedGrip = *dynamic_cast<Grip*>(button.Get());
			}
			else if (dynamic_cast<Stock*>(button.Get()))
			{
				this->m_EquipedStock = *dynamic_cast<Stock*>(button.Get());
			}
			else if (dynamic_cast<Magazine*>(button.Get()))
			{
				this->m_EquipedMag = *dynamic_cast<Magazine*>(button.Get());
			}
		}

		if (button.Hover(_window) && button.Get()->GetUnlockLevel() <= this->m_PlayerLevel)
		{
			this->m_PopUpRect.setPosition(button.Pos() + sf::Vector2f(260.f, 0));
			this->m_PopUpText.setPosition(this->m_PopUpRect.getPosition() + sf::Vector2f(5.f, 5.f));
			this->m_PopUp = true;

			if (dynamic_cast<Muzzle*>(button.Get()))
			{
				this->m_PopUpString = button.Get()->GetName()
					+ "\nSpread : " + (dynamic_cast<Muzzle*>(button.Get())->GetSpreadMod() > 1 ? "+" : "") + std::to_string(Tools::ToRoundPercent(dynamic_cast<Muzzle*>(button.Get())->GetSpreadMod())) + "%"
					+ "\nRange : " + (dynamic_cast<Muzzle*>(button.Get())->GetRangeMod() > 1 ? "+" : "") + std::to_string(Tools::ToRoundPercent(dynamic_cast<Muzzle*>(button.Get())->GetRangeMod())) + "%"
					+ "\nBullet Speed : " + (dynamic_cast<Muzzle*>(button.Get())->GetVelocityMod() > 1 ? "+" : "") + std::to_string(Tools::ToRoundPercent(dynamic_cast<Muzzle*>(button.Get())->GetVelocityMod())) + "%";
			}
			else if (dynamic_cast<Grip*>(button.Get()))
			{
				this->m_PopUpString = button.Get()->GetName()
					+ "\nAccuracy : " + (dynamic_cast<Grip*>(button.Get())->GetAccuracyMod() > 1 ? "+" : "") + std::to_string(Tools::ToRoundPercent(dynamic_cast<Grip*>(button.Get())->GetAccuracyMod())) + "%"
					+ "\nRecoil : " + (dynamic_cast<Grip*>(button.Get())->GetRecoilMod() > 1 ? "+" : "") + std::to_string(Tools::ToRoundPercent(dynamic_cast<Grip*>(button.Get())->GetRecoilMod())) + "%"
					+ "\nRate of fire : " + (dynamic_cast<Grip*>(button.Get())->GetROFMod() > 1 ? "+" : "") + std::to_string(Tools::ToRoundPercent(dynamic_cast<Grip*>(button.Get())->GetROFMod())) + "%";
			}
			else if (dynamic_cast<Stock*>(button.Get()))
			{
				this->m_PopUpString = button.Get()->GetName()
					+ "\nAccuracy : " + (dynamic_cast<Stock*>(button.Get())->GetAccuracyMod() > 1 ? "+" : "") + std::to_string(Tools::ToRoundPercent(dynamic_cast<Stock*>(button.Get())->GetAccuracyMod())) + "%"
					+ "\nRecoil : " + (dynamic_cast<Stock*>(button.Get())->GetRecoilMod() > 1 ? "+" : "") + std::to_string(Tools::ToRoundPercent(dynamic_cast<Stock*>(button.Get())->GetRecoilMod())) + "%"
					+ "\nWalking Speed : " + (dynamic_cast<Stock*>(button.Get())->GetWalkMod() > 1 ? "+" : "") + std::to_string(Tools::ToRoundPercent(dynamic_cast<Stock*>(button.Get())->GetWalkMod())) + "%";
			}
			else if (dynamic_cast<Magazine*>(button.Get()))
			{
				this->m_PopUpString = button.Get()->GetName()
					+ "\nCapacity : " + (std::to_string(dynamic_cast<Magazine*>(button.Get())->GetCapacity()));
			}

			this->m_PopUpText.setString(this->m_PopUpString);
		}

	}
	for (EquipmentButton& button : this->m_EquipmentList)
	{
		std::string currentName = button.Get()->GetName();
		if (currentName != this->m_EquipedArmor.GetName() && currentName != this->m_EquipedAmmoStash.GetName())
		{
			button.SetActive(false);
		}
		else
		{
			button.SetActive(true);
		}

		/// Temp ///
		if (this->m_EquipedArmor.GetUnlockLevel() > this->m_PlayerLevel)
		{
			this->m_EquipedArmor = Armor("None", 0, 0, 1.f);
		}
		if (this->m_EquipedAmmoStash.GetUnlockLevel() > this->m_PlayerLevel)
		{
			this->m_EquipedAmmoStash = AmmoStash("Ammo Pouch", 0, 0);
		}
		////////////

		if (button.Update(_window, button.Get()->GetUnlockLevel()))
		{
			if (dynamic_cast<Armor*>(button.Get()))
			{
				this->m_EquipedArmor = *dynamic_cast<Armor*>(button.Get());
			}
			else if (dynamic_cast<AmmoStash*>(button.Get()))
			{
				this->m_EquipedAmmoStash = *dynamic_cast<AmmoStash*>(button.Get());
			}
		}

		if (button.Hover(_window) && button.Get()->GetUnlockLevel() <= this->m_PlayerLevel)
		{
			this->m_PopUpRect.setPosition(button.Pos() + sf::Vector2f(260.f, 0));
			this->m_PopUpText.setPosition(this->m_PopUpRect.getPosition() + sf::Vector2f(5.f, 5.f));
			this->m_PopUp = true;

			if (dynamic_cast<Armor*>(button.Get()))
			{
				this->m_PopUpString = button.Get()->GetName()
					+ "\nLife : " + (std::to_string(dynamic_cast<Armor*>(button.Get())->GetLife()))
					+ "\nWalk Speed : " + (dynamic_cast<Armor*>(button.Get())->GetWalkSpeedMod() > 1 ? "+" : "") + std::to_string(Tools::ToRoundPercent(dynamic_cast<Armor*>(button.Get())->GetWalkSpeedMod())) + "%";
			}
			else if (dynamic_cast<AmmoStash*>(button.Get()))
			{
				this->m_PopUpString = button.Get()->GetName()
					+ "\nCapacity : " + (std::to_string(dynamic_cast<AmmoStash*>(button.Get())->GetCapacity()));
			}

			this->m_PopUpText.setString(this->m_PopUpString);
		}
	}
}

void Shop::Display(Window& _window)
{
	this->m_Text.setString("Attachment");
	this->m_Text.setPosition(sf::Vector2f(10.f,150));
	_window.Draw(this->m_Text);
	for (AttachmentButton& button : this->m_AttachementsList)
	{
		button.Display(_window);
	}

	this->m_Text.setString("Equipment");
	this->m_Text.setPosition(sf::Vector2f(10.f,600.f));
	_window.Draw(this->m_Text);
	for (EquipmentButton& button : this->m_EquipmentList)
	{
		button.Display(_window);
	}

	this->m_Text.setString("Player Level : " + std::to_string(this->m_PlayerLevel) + "[" + std::to_string(Level::GetXp()) + "]");
	this->m_Text.setPosition(sf::Vector2f(1200.f, 10.f));
	_window.Draw(this->m_Text);

	if (this->m_PopUp)
	{
		_window.Draw(this->m_PopUpRect);
		_window.Draw(this->m_PopUpText);
	}
}