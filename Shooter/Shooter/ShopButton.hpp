#pragma once
#include <string>
#include "Button.hpp"
#include "Attachment.hpp"
#include "Equipement.hpp"

class ShopButton : public Button
{
	protected :
		std::string m_Memory;
		bool m_Active = false;
	public:
		ShopButton() = default;
		ShopButton(std::string _str, sf::Vector2f _pos, sf::Vector2f _size, sf::Texture* _texture);
		~ShopButton() = default;

		sf::Vector2f Pos() { return this->m_Rect.getPosition(); }
		bool Hover() { return this->m_Rect.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition())); }

		void SetActive(bool _active) { this->m_Active = _active; }

		bool Update(Window& _window, int _linkedAttachmentLvl) override;
		void Display(Window& _window) override;
};

class AttachmentButton : public ShopButton
{
	private :
		Attachment* m_Attachement = nullptr;
	public :
		AttachmentButton() = default;
		AttachmentButton(std::string _str, sf::Vector2f _pos, sf::Vector2f _size, sf::Texture* _texture);
		~AttachmentButton() = default;


		void Bind(Attachment& _attachment);
		Attachment* Get() { return this->m_Attachement; }
};

class EquipmentButton : public ShopButton
{
	private:
		Equipment* m_Equipment = nullptr;
	public:
		EquipmentButton() = default;
		EquipmentButton(std::string _str, sf::Vector2f _pos, sf::Vector2f _size, sf::Texture* _texture);
		~EquipmentButton() = default;


		void Bind(Equipment& _equipment);
		Equipment* Get() { return this->m_Equipment; }
};