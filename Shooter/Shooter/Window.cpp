#include "Window.hpp"

//////////////////////////////////////////////////

View::View()
{
	this->m_View = sf::View();
}
View::View(const sf::Vector2f& _center, const sf::Vector2f& _size)
{
	this->m_View = sf::View(_center,_size);
}
View::~View()
{

}

//////////////////////////////////////////////////

Window::Window()
{
	this->m_Window.create(sf::VideoMode(1920, 1080), "Shooter", sf::Style::Fullscreen);
	this->m_Fullscreen = true;
}
Window::~Window()
{

}

void Window::Create(sf::VideoMode _videoMode,const sf::String& _title, sf::Uint32 _style)
{
	this->m_Window.create(_videoMode, _title, _style);
}

void Window::ToggleFullscreen()
{
	this->m_Fullscreen = !this->m_Fullscreen;
	this->m_Window.create(sf::VideoMode(1920, 1080), "Shooter", (this->m_Fullscreen ? sf::Style::Fullscreen : sf::Style::Default));
}
void Window::SetView(View _view)
{
	this->m_Window.setView(_view.GetView());
}
void Window::SetViewCenter(const sf::Vector2f& _center)
{
	sf::View view(this->m_Window.getView());
	view.setCenter(_center);
	this->m_Window.setView(view);
}
void Window::ResetView()
{
	this->m_Window.setView(this->m_Window.getDefaultView());
}

void Window::Clear()
{
	this->m_Window.clear();
}
void Window::Draw(const sf::Drawable& _drawable)
{
	this->m_Window.draw(_drawable);
}
void Window::Display()
{
	this->m_Window.display();
}

bool Window::IsOpen()
{ 
	return this->m_Window.isOpen(); 
}
bool Window::HasFocus()
{
	return this->m_Window.hasFocus();
}
bool Window::PollEvent(sf::Event& _event)
{
	return this->m_Window.pollEvent(_event);
}
void Window::Close()
{
	this->m_Window.close();
}

//////////////////////////////////////////////////