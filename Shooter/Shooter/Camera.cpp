#include "Camera.hpp"

void Camera::Reset()
{
	this->m_Target = sf::Vector2f(0.f, 0.f);
}

void Camera::Update(Window& _window)
{
	if (_window.GetViewCenter() != this->m_Target)
	{
		sf::Vector2f newCenter = _window.GetViewCenter() + Tools::Normalize(this->m_Target - _window.GetViewCenter()) * Time::GetDeltaTime() * 450.f;
		_window.SetViewCenter(newCenter);
	}
}

void Camera::NewTarget(Window& _window, sf::Vector2f _pos, sf::Vector2i _mapsize)
{
	sf::Vector2f target(_pos);

	target.x = (Tools::Max<float, float, float>((_window.GetSize().x / 2.f) - 32.f, Tools::Min<float, float, float>(_pos.x, (_mapsize.x * Tile::GetSize()) - _window.GetViewSize().x / 2.f) - 32.f));
	target.y = (Tools::Max<float, float, float>((_window.GetSize().y / 2.f) - 32.f, Tools::Min<float, float, float>(_pos.y, (_mapsize.y * Tile::GetSize()) - _window.GetViewSize().y / 2.f) - 32.f));

	this->m_Target = target;
}