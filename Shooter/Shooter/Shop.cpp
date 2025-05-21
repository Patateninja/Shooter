#include "Shop.hpp"

Shop::Shop()
{
	this->m_PlayerLevel = 0;
}
Shop::Shop(int _lvl)
{
	this->m_PlayerLevel = _lvl;

	this->m_EquipedMuzzle = Muzzle("Default Muzzle", 0, 1.f, 1.f, 1.f);
	this->m_EquipedGrip = Grip("Default Grip", 0, 1.f, 1.f, 1.f);
	this->m_EquipedStock = Stock("Default Stock", 0, 1.f, 1.f, 1.f);
	this->m_EquipedMag = Magazine("Default Magazine", 0, 1);


	#pragma region Muzzle
	this->m_AttachementsList.push_back(std::make_pair<AttachmentButton, Attachment*>(AttachmentButton(std::string("Default"),sf::Vector2f(10.f,150.f),sf::Vector2f(350.f,75.f), nullptr), new Muzzle("Default Muzzle", 0, 1.f, 1.f, 1.f)));
	this->m_AttachementsList.push_back(std::make_pair<AttachmentButton, Attachment*>(AttachmentButton(std::string("Choke Muzzle"), sf::Vector2f(380.f, 150.f), sf::Vector2f(350.f, 75.f), nullptr), new Muzzle("Choke Muzzle", 3, 0.5f, 1.3f, 1.2f)));
	this->m_AttachementsList.push_back(std::make_pair<AttachmentButton, Attachment*>(AttachmentButton(std::string("Muzzle Brake"), sf::Vector2f(750.f, 150.f), sf::Vector2f(350.f, 75.f), nullptr), new Muzzle("Muzzle Brake", 8, 0.7f, 1.2f, 1.5f)));
	this->m_AttachementsList.push_back(std::make_pair<AttachmentButton, Attachment*>(AttachmentButton(std::string("Sawed Off"), sf::Vector2f(1120.f, 150.f), sf::Vector2f(350.f, 75.f), nullptr), new Muzzle("Sawed Off", 20, 2.f, 1.2f, 0.5f)));
	#pragma endregion

	#pragma region Grip
	this->m_AttachementsList.push_back(std::make_pair<AttachmentButton, Attachment*>(AttachmentButton(std::string("Default"), sf::Vector2f(10.f, 250.f), sf::Vector2f(350.f, 75.f), nullptr), new Grip("Default Grip", 0, 1.f, 1.f, 1.f)));
	this->m_AttachementsList.push_back(std::make_pair<AttachmentButton, Attachment*>(AttachmentButton(std::string("Vertical Grip"), sf::Vector2f(380.f, 250.f), sf::Vector2f(350.f, 75.f), nullptr), new Grip("Vertical Grip", 4, 1.5f, 0.85f, 1.1f)));
	this->m_AttachementsList.push_back(std::make_pair<AttachmentButton, Attachment*>(AttachmentButton(std::string("Horizontal Grip"), sf::Vector2f(750.f, 250.f), sf::Vector2f(350.f, 75.f), nullptr), new Grip("Horizontal Grip", 9, 1.1f, 0.5f, 1.15f)));
	this->m_AttachementsList.push_back(std::make_pair<AttachmentButton, Attachment*>(AttachmentButton(std::string("Speed Grip"), sf::Vector2f(1120.f, 250.f), sf::Vector2f(350.f, 75.f), nullptr), new Grip("Speed Grip", 18, 1.15f, 0.9f, 1.5f)));
	#pragma endregion

	#pragma region Stock
	this->m_AttachementsList.push_back(std::make_pair<AttachmentButton, Attachment*>(AttachmentButton(std::string("Default"), sf::Vector2f(10.f, 350.f), sf::Vector2f(350.f, 75.f), nullptr), new Stock("Default Stock", 0, 1.f, 1.f, 1.f)));
	this->m_AttachementsList.push_back(std::make_pair<AttachmentButton, Attachment*>(AttachmentButton(std::string("Light Recon \nStock"), sf::Vector2f(380.f, 350.f), sf::Vector2f(350.f, 75.f), nullptr), new Stock("Light Recon Stock", 5, 1.25f, 0.85f, 1.1f)));
	this->m_AttachementsList.push_back(std::make_pair<AttachmentButton, Attachment*>(AttachmentButton(std::string("Heavy Assault \nStock"), sf::Vector2f(750.f, 350.f), sf::Vector2f(350.f, 75.f), nullptr), new Stock("Heavy Assault Stock", 10, 0.9f, 0.5f, 1.f)));
	this->m_AttachementsList.push_back(std::make_pair<AttachmentButton, Attachment*>(AttachmentButton(std::string("No Stock"), sf::Vector2f(1120.f, 350.f), sf::Vector2f(350.f, 75.f), nullptr), new Stock("No Stock", 26, 2.f, 1.5f, 1.25f)));
	#pragma endregion

	#pragma region Magazine
	this->m_AttachementsList.push_back(std::make_pair<AttachmentButton, Attachment*>(AttachmentButton(std::string("Default"), sf::Vector2f(10.f, 450.f), sf::Vector2f(350.f, 75.f), nullptr), new Magazine("Default Magazine", 0, 0)));
	this->m_AttachementsList.push_back(std::make_pair<AttachmentButton, Attachment*>(AttachmentButton(std::string("6 Shell Tube"), sf::Vector2f(380.f, 450.f), sf::Vector2f(350.f, 75.f), nullptr), new Magazine("6 Shell Tube", 6, 2)));
	this->m_AttachementsList.push_back(std::make_pair<AttachmentButton, Attachment*>(AttachmentButton(std::string("8 Shell Tube"), sf::Vector2f(750.f, 450.f), sf::Vector2f(350.f, 75.f), nullptr), new Magazine("8 Shell Tube", 14, 4)));
	this->m_AttachementsList.push_back(std::make_pair<AttachmentButton, Attachment*>(AttachmentButton(std::string("12 Shell Drum"), sf::Vector2f(1120.f, 450.f), sf::Vector2f(350.f, 75.f), nullptr), new Magazine("12 Shell Drum", 29, 8)));
	#pragma endregion
}

void Shop::LockItem()
{
	for (auto& [button, attachment] : this->m_AttachementsList)
	{
		if (attachment->GetUnlockLevel() > this->m_PlayerLevel)
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

	for (auto& [button, attachment] : this->m_AttachementsList)
	{
		if (attachment->GetName() != this->m_EquipedGrip.GetName() && attachment->GetName() != this->m_EquipedMag.GetName() && attachment->GetName() != this->m_EquipedMuzzle.GetName() && attachment->GetName() != this->m_EquipedStock.GetName())
		{
			button.SetActive(false);
		}

		if (button.Update(attachment->GetUnlockLevel()))
		{
			if (dynamic_cast<Muzzle*>(attachment))
			{
				this->m_EquipedMuzzle = *dynamic_cast<Muzzle*>(attachment);
			}
			else if(dynamic_cast<Grip*>(attachment))
			{
				this->m_EquipedGrip = *dynamic_cast<Grip*>(attachment);
			}
			else if (dynamic_cast<Stock*>(attachment))
			{
				this->m_EquipedStock = *dynamic_cast<Stock*>(attachment);
			}
			else if (dynamic_cast<Magazine*>(attachment))
			{
				this->m_EquipedMag = *dynamic_cast<Magazine*>(attachment);
			}
		}
	}
}

void Shop::Display(Window& _window)
{
	for (auto& [button, attachment] : this->m_AttachementsList)
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