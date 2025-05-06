#pragma once
#include "Tools.hpp"

class View
{
	private :
		sf::View m_View;
	public :
		View();
		View(const sf::Vector2f& _center, const sf::Vector2f& size);
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
		void SetViewCenter(const sf::Vector2f& _center);
		void ResetView();

		void Clear();
		void Draw(const sf::Drawable& _drawable);
		void Display();

		bool IsOpen();
		bool PollEvent(sf::Event& _event);
		void Close();

		template<typename T>
		sf::Vector2f RelativePos(const sf::Vector2<T>& _vector)
		{
			return this->m_Window.mapPixelToCoords(sf::Vector2i(_vector));
		}
};

namespace Win
{
	Window& GetWindow();

	void Create(sf::VideoMode _videoMode, const sf::String& _title, sf::Uint32 _style);

	void ToggleFullscreen();
	void SetView(const View& _view);
	void SetViewCenter(const sf::Vector2f& _center);
	void ResetView();

	void Clear();
	void Draw(const sf::Drawable& _drawable);
	void Display();

	bool IsOpen();
	bool PollEvent(sf::Event& _event);
	void Close();
}