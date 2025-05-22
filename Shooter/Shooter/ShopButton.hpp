#pragma once
#include "Button.hpp"
#include "Attachment.hpp"

class Equipment
{
	public :
		int GetUnlockedLevel() { return 0; }
};

class ShopButton : public Button
{
	protected :
		bool m_Active = false;
		std::string m_Memory;
	public:
		ShopButton() = default;
		ShopButton(std::string _str, sf::Vector2f _pos, sf::Vector2f _size, sf::Texture* _texture);
		~ShopButton() = default;

		inline void SetActive(bool _active) { this->m_Active = _active; }

		bool Update(int _linkedAttachementLvl) override;
		void Display(Window& _window) override;
};

class AttachmentButton : public ShopButton
{
	private :
		Attachment m_Attachement;
	public :
		AttachmentButton() = default;
		AttachmentButton(std::string _str, sf::Vector2f _pos, sf::Vector2f _size, sf::Texture* _texture);
		~AttachmentButton() = default;

		void Bind(Attachment& _attachment);
		Attachment& Get() { return this->m_Attachement; }
};

class EquipmentButton : public ShopButton
{
	private:
		Equipment m_Equipment;
	public:
		EquipmentButton() = default;
		~EquipmentButton() = default;

		void Bind(Equipment& _equipment);
		Equipment& Get() { return this->m_Equipment; }
};