#pragma once
#include "Attachment.hpp"
#include "ShopButton.hpp"

class Shop
{
	private :
		sf::Text m_Text;
		Muzzle m_EquipedMuzzle;
		Grip m_EquipedGrip;
		Stock m_EquipedStock;
		Magazine m_EquipedMag;
		std::list<AttachmentButton> m_AttachementsList;
		std::list<EquipmentButton> m_EquipmentList;
		int m_PlayerLevel;
	public :
		Shop();
		Shop(int _lvl);
		~Shop() = default;

		void LockItem();

		void AddAttachment(std::string& _buttonName, sf::Vector2f& _buttonPos, std::string& _textureName, sf::Vector2f _buttonSize, Attachment& _attachment);
		void AddEquipement(std::string& _buttonName, sf::Vector2f& _buttonPos, std::string& _textureName, sf::Vector2f _buttonSize, Equipment& _equipment);

		void Update();
		void Display(Window& _window);

		void SetLevel(int _lvl) { this->m_PlayerLevel = _lvl; }
};