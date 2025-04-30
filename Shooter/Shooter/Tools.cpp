#include "Tools.hpp"

float Tools::GetDeltaTime(sf::Clock& _clock)
{
	return _clock.getElapsedTime().asSeconds();
}

float Tools::VectorsToAngle(sf::Vector2f const _vect1, sf::Vector2f const _vect2)
{
	float x = (_vect1.x * _vect2.x) + (_vect1.y * _vect2.y);
	float y = (_vect1.x * _vect2.y) - (_vect1.y * _vect2.x);
	return std::atan2(y, x);
}

float Tools::VectorToAngle(sf::Vector2f const _vect)
{
	sf::Vector2f vect(0.f, -1.f);
	return Tools::VectorsToAngle(_vect, vect);
}

sf::Vector2f Tools::AngleToVector(float const _len, float const _angle)
{
	return sf::Vector2f(std::cos(_angle) * _len, std::sin(_angle) * _len);
}

float Tools::Magnitude(sf::Vector2f const _vect)
{
	return std::sqrt(std::pow(_vect.x, 2.0) + std::pow(_vect.y, 2.0));
}

sf::Vector2f Tools::Normalize(sf::Vector2f const _vect)
{
	return sf::Vector2f(_vect.x / Tools::Magnitude(_vect), _vect.y / Tools::Magnitude(_vect));
}
