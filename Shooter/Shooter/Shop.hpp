#pragma once
#include "Attachment.hpp"
#include "Button.hpp"

class Shop
{
	private :
		int m_PlayerLevel;
		std::list<std::pair<AttachmentButton, Attachment*>> m_AttachementsList;
		Muzzle m_EquipedMuzzle;
		Grip m_EquipedGrip;
		Stock m_EquipedStock;
		Magazine m_EquipedMag;
	public :
		Shop();
		Shop(int _lvl);
		~Shop() = default;

		void LockItem();

		void Update();
		void Display(Window& _window);

		void SetLevel(int _lvl) { this->m_PlayerLevel = _lvl; }
};