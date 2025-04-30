#include "Tools.hpp"

float Tools::GetDeltaTime(sf::Clock& _clock)
{
	return _clock.getElapsedTime().asSeconds();
}

float Tools::Magnitude(sf::Vector2f& _vect)
{
	return std::sqrt(std::pow(_vect.x, 2.0) + std::pow(_vect.y, 2.0));
}