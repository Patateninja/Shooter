#pragma once
#include "Window.hpp"
#include "Projectile.hpp"

class Shield
{
	private :
		sf::RectangleShape m_Rect;
		bool m_Active = true;
	public :
		Shield(sf::Vector2f _pos);
		~Shield() = default;

		inline const bool GetActive() const { return this->m_Active; };
		
		inline void SetActive(bool _active) { this->m_Active = _active; };
		inline void SetPos(sf::Vector2f _pos) { this->m_Rect.setPosition(_pos); };
		inline void SetAngle(float _angle) { this->m_Rect.setRotation(_angle); };

		void Udpate(bool _active, sf::Vector2f _pos, float _angle);
		void Display(Window& _window);

		void CheckContact();
};