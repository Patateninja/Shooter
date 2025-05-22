#pragma once
#include "Attachment.hpp"
#include "ShopButton.hpp"

class Shop
{
	private :
		int m_PlayerLevel;
		std::list<AttachmentButton> m_AttachementsList;
		std::list<EquipmentButton> m_EquipmentList;
		Muzzle m_EquipedMuzzle;
		Grip m_EquipedGrip;
		Stock m_EquipedStock;
		Magazine m_EquipedMag;
	public :
		Shop();
		Shop(int _lvl);
		~Shop() = default;

		void LockItem();

		void AddAttachment();
		void AddEquipement();

		void Update();
		void Display(Window& _window);

		void SetLevel(int _lvl) { this->m_PlayerLevel = _lvl; }
};