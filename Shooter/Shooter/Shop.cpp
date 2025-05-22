#include "Shop.hpp"

Shop::Shop()
{
	this->m_PlayerLevel = 0;
}
Shop::Shop(int _lvl)
{
	this->m_PlayerLevel = _lvl;

	this->m_EquipedMuzzle = Muzzle("Default Muzzle"    , 0, 1.f, 1.f, 1.f);
	this->m_EquipedGrip =   Grip("Default Grip"        , 0, 1.f, 1.f, 1.f);
	this->m_EquipedStock =  Stock("Default Stock"      , 0, 1.f, 1.f, 1.f);
	this->m_EquipedMag =    Magazine("Default Magazine", 0, 1);

	sf::Vector2f buttonsize(250.f, 75.f);

	#pragma region Muzzle
	this->m_AttachementsList.push_back(AttachmentButton(std::string("Default"),      sf::Vector2f(10.f, 150.f),  buttonsize, nullptr));
	Muzzle("Default Muzzle", 0, 1.f, 1.f, 1.f);
	this->m_AttachementsList.push_back(AttachmentButton(std::string("Choke Muzzle"), sf::Vector2f(280.f, 150.f), buttonsize, nullptr));
	Muzzle("Choke Muzzle", 3, 0.5f, 1.3f, 1.2f);
	this->m_AttachementsList.push_back(AttachmentButton(std::string("Muzzle Brake"), sf::Vector2f(550.f, 150.f), buttonsize, nullptr));
	Muzzle("Muzzle Brake"  , 10, 0.7f, 1.2f, 1.5f);
	this->m_AttachementsList.push_back(AttachmentButton(std::string("Sawed Off"),    sf::Vector2f(820.f, 150.f), buttonsize, nullptr));
	Muzzle("Sawed Off", 20, 2.f, 1.2f, 0.5f);
	#pragma endregion

	#pragma region Grip
	this->m_AttachementsList.push_back(AttachmentButton(std::string("Default"),         sf::Vector2f(10.f, 250.f),  buttonsize, nullptr));
	Grip("Default Grip", 0, 1.f, 1.f, 1.f);
	this->m_AttachementsList.push_back(AttachmentButton(std::string("Vertical Grip"),   sf::Vector2f(280.f, 250.f), buttonsize, nullptr));
	Grip("Vertical Grip"  , 4 , 1.5f , 0.85f, 1.1f);
	this->m_AttachementsList.push_back(AttachmentButton(std::string("Horizontal Grip"), sf::Vector2f(550.f, 250.f), buttonsize, nullptr));
	Grip("Horizontal Grip", 9 , 1.1f , 0.5f , 1.15f);
	this->m_AttachementsList.push_back(AttachmentButton(std::string("Speed Grip"),      sf::Vector2f(820.f, 250.f), buttonsize, nullptr));
	Grip("Speed Grip"     , 18, 1.15f, 0.9f , 1.5f);
	#pragma endregion

	#pragma region Stock
	this->m_AttachementsList.push_back(AttachmentButton(std::string("Default"),             sf::Vector2f(10.f, 350.f),  buttonsize, nullptr));
	Stock("Default Stock"      , 0 , 1.f  , 1.f  , 1.f);
	this->m_AttachementsList.push_back(AttachmentButton(std::string("Light Recon Stock"),   sf::Vector2f(280.f, 350.f), buttonsize, nullptr));
	Stock("Light Recon Stock"  , 5 , 1.25f, 0.85f, 1.1f);
	this->m_AttachementsList.push_back(AttachmentButton(std::string("Heavy Assault Stock"), sf::Vector2f(550.f, 350.f), buttonsize, nullptr));
	Stock("Heavy Assault Stock", 8 , 0.9f , 0.5f , 1.f);
	this->m_AttachementsList.push_back(AttachmentButton(std::string("No Stock"),            sf::Vector2f(820.f, 350.f), buttonsize, nullptr));
	Stock("No Stock"           , 26, 2.f  , 1.5f , 1.25f);
	#pragma endregion

	#pragma region Magazine
	this->m_AttachementsList.push_back(AttachmentButton(std::string("Default"),       sf::Vector2f(10.f, 450.f),  buttonsize, nullptr));
	Magazine("Default Magazine", 0 , 1);
	this->m_AttachementsList.push_back(AttachmentButton(std::string("6 Shell Tube"),  sf::Vector2f(280.f, 450.f), buttonsize, nullptr));
	Magazine("6 Shell Tube"    , 6 , 2);
	this->m_AttachementsList.push_back(AttachmentButton(std::string("8 Shell Tube"),  sf::Vector2f(550.f, 450.f), buttonsize, nullptr));
	Magazine("8 Shell Tube"    , 14, 4);
	this->m_AttachementsList.push_back(AttachmentButton(std::string("12 Shell Drum"), sf::Vector2f(820.f, 450.f), buttonsize, nullptr));
	Magazine("12 Shell Drum"   , 29, 8);
	#pragma endregion

	#pragma region Armor

	#pragma 
}

void Shop::LockItem()
{
	for (AttachmentButton& button : this->m_AttachementsList)
	{
		if (button.Get().GetUnlockLevel() > this->m_PlayerLevel)
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
		if (button.Get().GetUnlockedLevel() > this->m_PlayerLevel)
		{
			button.Lock();
		}
		else
		{
			button.Unlock();
		}
	}
}

void Shop::Update()
{
	this->LockItem(); //Move to constructor after debug


	for (AttachmentButton& button : this->m_AttachementsList)
	{
		if (button.Get().GetName() != this->m_EquipedGrip.GetName() && button.Get().GetName() != this->m_EquipedMag.GetName() && button.Get().GetName() != this->m_EquipedMuzzle.GetName() && button.Get().GetName() != this->m_EquipedStock.GetName())
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
		else if (this->m_EquipedGrip.GetUnlockLevel() > this->m_PlayerLevel)
		{
			this->m_EquipedGrip = Grip("Default Grip", 0, 1.f, 1.f, 1.f);
		}
		else if (this->m_EquipedStock.GetUnlockLevel() > this->m_PlayerLevel)
		{
			this->m_EquipedStock = Stock("Default Stock", 0, 1.f, 1.f, 1.f);
		}
		else if (this->m_EquipedMag.GetUnlockLevel() > this->m_PlayerLevel)
		{
			this->m_EquipedMag = Magazine("Default Magazine", 0, 1);
		}
		////////////

		if (button.Update(button.Get().GetUnlockLevel()))
		{
			if (dynamic_cast<Muzzle*>(&button.Get()))
			{
				this->m_EquipedMuzzle = *dynamic_cast<Muzzle*>(&button.Get());
			}
			else if(dynamic_cast<Grip*>(&button.Get()))
			{
				this->m_EquipedGrip = *dynamic_cast<Grip*>(&button.Get());
			}
			else if (dynamic_cast<Stock*>(&button.Get()))
			{
				this->m_EquipedStock = *dynamic_cast<Stock*>(&button.Get());
			}
			else if (dynamic_cast<Magazine*>(&button.Get()))
			{
				this->m_EquipedMag = *dynamic_cast<Magazine*>(&button.Get());
			}
		}
	}
}

void Shop::Display(Window& _window)
{

	for (AttachmentButton& button : this->m_AttachementsList)
	{
		button.Display(_window);
	}

	sf::Text txt("Player Level : " + std::to_string(this->m_PlayerLevel)
				+ "\nGrip : " + this->m_EquipedGrip.GetName()
				+ "\nStock : " + this->m_EquipedStock.GetName()
				+ "\nMagazine : " + this->m_EquipedMag.GetName()
				+ "\nMuzzle : " + this->m_EquipedMuzzle.GetName() + "\n", RscMana::Get<sf::Font>("Mono"));
	txt.setPosition(sf::Vector2f(10.f, 550.f));
	_window.Draw(txt);
}