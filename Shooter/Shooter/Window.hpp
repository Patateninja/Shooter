#pragma once
#include "Tools.hpp"

class View
{
	private :
		sf::View m_View;
	public :
		View();
		View(sf::Vector2f _center, sf::Vector2f size);
		View(sf::View _view);
		~View();

		inline sf::View GetView() { return this->m_View; };
};

class Window
{
	private :
		sf::RenderWindow m_Window;
		bool m_Fullscreen;
	public :
		Window();
		~Window();
		
		void Create(sf::VideoMode _videoMode,const sf::String& _title, sf::Uint32 _style);

		void ToggleFullscreen();
		void SetView(View _view);

		void Clear();
		void Draw(sf::Drawable& _drawable);
		void Display();

		bool IsOpen();
		bool PollEvent(sf::Event& _event);
		void Close();
};