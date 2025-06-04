#pragma once
#include "Attachment.hpp"
#include "ShopButton.hpp"
#include "Xp.hpp"

class Shop
{
	private :
		sf::Text m_Text;
		sf::Text m_PopUpText;
		sf::RectangleShape m_PopUpRect;
		Muzzle m_EquipedMuzzle;
		Grip m_EquipedGrip;
		Stock m_EquipedStock;
		Magazine m_EquipedMag;
		Armor m_EquipedArmor;
		AmmoStash m_EquipedAmmoStash;
		std::list<AttachmentButton> m_AttachementsList;
		std::list<EquipmentButton> m_EquipmentList;
		std::string m_PopUpString;
		int m_PlayerLevel = 0;
		bool m_PopUp = false;
	public :
		Shop() = default;
		Shop(int _lvl, Muzzle& _muzzle, Grip& _grip, Stock& _stock, Magazine& _magazine, Armor& _armor, AmmoStash& _ammostash);
		~Shop() = default;

		void LockItem();

		template<typename T>
		void AddAttachment(std::string _buttonName, sf::Vector2f _buttonPos, sf::Vector2f _buttonSize, std::string _textureName, T* _attachment);
		template<typename T>
		void AddEquipment(std::string _buttonName, sf::Vector2f _buttonPos, sf::Vector2f _buttonSize, std::string _textureName, T* _equipment);;

		void Update(Window& _window);
		void Display(Window& _window);

		void SetLevel(int _lvl) { this->m_PlayerLevel = _lvl; }

		inline Muzzle GetMuzzle() { return this->m_EquipedMuzzle; }
		inline Grip GetGrip() { return this->m_EquipedGrip; }
		inline Stock GetStock() { return this->m_EquipedStock; }
		inline Magazine GetMagazine() { return this->m_EquipedMag; }
		inline Armor GetArmor() { return this->m_EquipedArmor; }
		inline AmmoStash GetAmmoStash() { return this->m_EquipedAmmoStash; }
};