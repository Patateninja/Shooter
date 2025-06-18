#include "ReloadButton.hpp"

ReloadButton::ReloadButton(std::string _str, std::string _strPopUp, sf::Vector2f _pos, sf::Vector2f _size, sf::Texture* _texture)
{
	this->m_Text.setString(_str);
	this->m_Text.setFont(RscMana::Get<sf::Font>("Pixel"));
	this->m_Text.setPosition(_pos + sf::Vector2f(1.f, 1.f));
	
	this->m_Rect.setPosition(_pos);
	this->m_Rect.setSize(_size);
	this->m_Rect.setTexture(_texture);

	this->m_PopUpText.setFont(RscMana::Get<sf::Font>("Mono"));
	this->m_PopUpText.setPosition(_pos + sf::Vector2f(_size.x + 1, 1));
	this->m_PopUpText.setString(_strPopUp);
	this->m_PopUpText.setCharacterSize(20);

	this->m_PopUpRect.setSize(this->m_PopUpText.getGlobalBounds().getSize() + sf::Vector2f(10.f, 10.f));
	this->m_PopUpRect.setPosition(_pos + sf::Vector2f(_size.x + 10.f, 0.f));
	this->m_PopUpRect.setFillColor(Color::DarkGrey);
	this->m_PopUpRect.setOutlineColor(Color::Grey);
	this->m_PopUpRect.setOutlineThickness(2);
}

void ReloadButton::SetPosition(Window& _window, sf::Vector2f _pos)
{
	this->m_Rect.setPosition(_pos);
	this->m_Text.setOrigin(this->m_Text.getGlobalBounds().getSize() / 2.f + this->m_Text.getLocalBounds().getPosition());
	this->m_Text.setPosition(this->m_Rect.getPosition() + (this->m_Rect.getSize() / 2.f));
	
	this->m_PopUpRect.setPosition(_pos + sf::Vector2f(this->m_Rect.getSize().x + 10, 0));
	this->m_PopUpText.setPosition(_pos + sf::Vector2f(this->m_Rect.getSize().x + 11, 1));
}

void ReloadButton::SetPopUpText(std::string _str)
{
	this->m_PopUpText.setPosition(this->m_Rect.getPosition() + sf::Vector2f(float(this->m_Rect.getSize().x) + 1, 1));
	this->m_PopUpText.setString(_str);

	this->m_PopUpRect.setSize(this->m_PopUpText.getGlobalBounds().getSize() + sf::Vector2f(10.f, 10.f));
	this->m_PopUpRect.setPosition(this->m_Rect.getPosition() + sf::Vector2f(this->m_Rect.getSize().x + 10, 0));
}
void ReloadButton::SetPopUpTexture(std::string _texturename)
{
	this->m_Rect.setTexture(&RscMana::Get<sf::Texture>(_texturename));
}

bool ReloadButton::Update(Window& _window)
{
	if (this->m_Rect.getGlobalBounds().contains(_window.RelativePos(sf::Mouse::getPosition(_window.Unwrap()))))
	{
		this->m_Rect.setFillColor(Color::LightGrey);
		if (!this->m_HoverSoundPlayed)
		{
			RscMana::Get<sf::Sound>("ButtonHover").play();
		}
		this->m_HoverSoundPlayed = true;
		this->m_DisplayPopUp = true;
	}
	else
	{
		this->m_Rect.setFillColor(Color::Grey);
		this->m_HoverSoundPlayed = false;
		this->m_DisplayPopUp = false;
	}

	return this->Clicked(_window);
}

void ReloadButton::Display(Window& _window)
{
	_window.Draw(this->m_Rect);
	_window.Draw(this->m_Text);
	if (this->m_DisplayPopUp)
	{
		_window.Draw(this->m_PopUpRect);
		_window.Draw(this->m_PopUpText);
	}
}