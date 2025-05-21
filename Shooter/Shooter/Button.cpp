#include "Button.hpp"

//////////////////////////////////////////////////

Button::Button(std::string _str, sf::Vector2f _pos, sf::Vector2f _size, sf::Texture* _texture)
{
	this->m_Text.setString(_str);
	this->m_Text.setFont(RscMana::Get<sf::Font>("Mono"));
	this->m_Text.setPosition(_pos + sf::Vector2f(1.f, 1.f));
	this->m_Rect.setPosition(_pos);
	this->m_Rect.setSize(_size);
	this->m_Rect.setTexture(_texture);
}

bool Button::Clicked()
{
	if (!this->m_Locked && sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->m_Rect.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())))
	{
		return true;
	}

	return false;
}

bool Button::Update(int)
{
	if (this->m_Rect.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())))
	{
		this->m_Rect.setFillColor(Color::LightGrey);
	}
	else
	{
		this->m_Rect.setFillColor(Color::Grey);
	}

	return this->Clicked();
}

void Button::Display(Window& _window)
{
	_window.Draw(this->m_Rect);
	_window.Draw(this->m_Text);
}

//////////////////////////////////////////////////

AttachmentButton::AttachmentButton(std::string _str, sf::Vector2f _pos, sf::Vector2f _size, sf::Texture* _texture)
{
	this->m_Memory = _str;
	this->m_Text.setString(_str);
	this->m_Text.setFont(RscMana::Get<sf::Font>("Mono"));
	this->m_Text.setPosition(_pos + sf::Vector2f(1.f, 1.f));
	this->m_Rect.setPosition(_pos);
	this->m_Rect.setSize(_size);
	this->m_Rect.setTexture(_texture);
	this->m_Active = false;
}

bool AttachmentButton::Update(int _linkedAttachementLvl)
{
	if (this->m_Locked)
	{
		this->m_Text.setString("Unlocked at lvl." + std::to_string(_linkedAttachementLvl));
	}
	else
	{
		this->m_Text.setString(this->m_Memory);

	}

	if (Button::Update(_linkedAttachementLvl))
	{
		this->m_Active = true;
		return true;
	}
	return false;
}

void AttachmentButton::Display(Window& _window)
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

	Button::Display(_window);
}

//////////////////////////////////////////////////