#include "ShopButton.hpp"

//////////////////////////////////////////////////

ShopButton::ShopButton(std::string _str, sf::Vector2f _pos, sf::Vector2f _size, sf::Texture* _texture)
{
	this->m_Memory = _str;
	this->m_Text.setString(_str);
	this->m_Text.setFont(RscMana::Get<sf::Font>("Mono"));
	this->m_Text.setCharacterSize(20);
	this->m_Text.setPosition(_pos + sf::Vector2f(1.f, 1.f));
	this->m_Rect.setPosition(_pos);
	this->m_Rect.setSize(_size);
	this->m_Rect.setTexture(_texture);
	this->m_Active = false;

}

bool ShopButton::Update(Window& _window, int _linkedAttachementLvl)
{
	if (this->m_Locked)
	{
		this->m_Text.setString("Unlocked at lvl." + std::to_string(_linkedAttachementLvl));
	}
	else
	{
		this->m_Text.setString(this->m_Memory);

		if (this->Button::Update(_window, 0))
		{
			this->m_Active = true;
			return true;
		}
	}

	return false;
}

void ShopButton::Display(Window& _window)
{
	if (this->m_Locked)
	{
		this->m_Rect.setFillColor(Color::DarkRed);
		this->m_Rect.setOutlineColor(Color::LightRed);
		this->m_Text.setFillColor(Color::LightRed);
		this->m_Rect.setOutlineThickness(5.f);
	}
	else if (this->m_Active)
	{
		this->m_Rect.setFillColor(Color::Grey);
		this->m_Rect.setOutlineColor(sf::Color::Green);
		this->m_Text.setFillColor(sf::Color::White);
		this->m_Rect.setOutlineThickness(5.f);
	}
	else
	{
		this->m_Rect.setOutlineColor(Color::DarkGrey);
		this->m_Text.setFillColor(sf::Color::White);
		this->m_Rect.setOutlineThickness(5.f);
	}

	this->Button::Display(_window);
}

//////////////////////////////////////////////////

AttachmentButton::AttachmentButton(std::string _str, sf::Vector2f _pos, sf::Vector2f _size, sf::Texture* _texture)
{
	this->ShopButton::ShopButton(_str, _pos, _size, _texture);
}

void AttachmentButton::Bind(Attachment& _attachment)
{
	this->m_Attachement = &_attachment;
}

//////////////////////////////////////////////////

EquipmentButton::EquipmentButton(std::string _str, sf::Vector2f _pos, sf::Vector2f _size, sf::Texture* _texture)
{
	this->ShopButton::ShopButton(_str, _pos, _size, _texture);
}

void EquipmentButton::Bind(Equipment& _equipment)
{
	this->m_Equipment = &_equipment;
}

//////////////////////////////////////////////////