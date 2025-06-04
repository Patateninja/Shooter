#pragma once
#include "Tools.hpp"

class View
{
	private :
		sf::View m_View;
	public :
		View();
		View(const sf::Vector2f& _center, const sf::Vector2f& size);
		View(const sf::View& _wiew);
		~View();

		inline sf::View GetView() { return this->m_View; };
		inline sf::Vector2f GetSize() { return this->m_View.getSize(); }
		inline sf::Vector2f GetCenter() { return this->m_View.getCenter(); }

		inline void SetCenter(sf::Vector2f _center) { this->m_View.setCenter(_center); }
		inline void SetSize(sf::Vector2f _size) { this->m_View.setSize(_size); }

		inline float Left() { return this->m_View.getCenter().x - (this->m_View.getSize().x / 2.f); }
		inline float Right() { return this->m_View.getCenter().x + (this->m_View.getSize().x / 2.f); }
		inline float Top() { return this->m_View.getCenter().y - (this->m_View.getSize().y / 2.f); }
		inline float Down() { return this->m_View.getCenter().y + (this->m_View.getSize().y / 2.f); }
};

class Window
{
	private :
		sf::RenderWindow m_Window;
		View m_View;
		bool m_Fullscreen;
	public :
		Window();
		~Window();
		
		void Create(sf::VideoMode _videoMode,const sf::String& _title, sf::Uint32 _style);

		inline sf::RenderWindow& Unwrap() { return this->m_Window; }
		inline View GetView() { return this->m_View; }
		inline View GetDefaultView() { return View(this->m_Window.getDefaultView()); }
		inline sf::Vector2u GetSize() { return this->m_Window.getSize(); }
		inline sf::Vector2f GetViewSize() { return this->m_View.GetSize(); }
		inline sf::Vector2f GetViewCenter() { return this->m_View.GetCenter(); }
		inline float GetViewLeft() { return this->m_View.Left(); }
		inline float GetViewRight() { return this->m_View.Right(); }
		inline float GetViewTop() { return this->m_View.Top(); }
		inline float GetViewDown() { return this->m_View.Down(); }

		void ToggleFullscreen();
		void SetView(View _view);
		void SetViewCenter(const sf::Vector2f& _center);
		void ResetView();

		void Clear();
		void Draw(const sf::Drawable& _drawable);
		void Display();

		bool IsOpen();
		bool HasFocus();
		bool PollEvent(sf::Event& _event);
		void Close();

		template<typename T>
		sf::Vector2f RelativePos(const sf::Vector2<T>& _vector)
		{
			return this->m_Window.mapPixelToCoords(sf::Vector2i(_vector));
		}
};