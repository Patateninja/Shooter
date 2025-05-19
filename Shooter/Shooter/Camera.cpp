#include "Camera.hpp"

void Camera::Update(Window& _window, sf::Vector2f _playerPos, sf::Vector2i _mapsize)
{
	sf::Vector2f center(_playerPos);

	center.x = (Tools::Max<float, float, float>((_window.GetSize().x / 2.f) - 32.f, Tools::Min<float, float, float>(_playerPos.x, (_mapsize.x * Tile::GetSize()) - _window.GetViewSize().x / 2.f) - 32.f));
	center.y = (Tools::Max<float, float, float>((_window.GetSize().y / 2.f) - 32.f, Tools::Min<float, float, float>(_playerPos.y, (_mapsize.y * Tile::GetSize()) - _window.GetViewSize().y / 2.f) - 32.f));

	_window.SetViewCenter(center);
}