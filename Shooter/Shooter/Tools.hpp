#pragma once
#include "SFML/Graphics.hpp"
#include <cmath>

namespace Tools
{
	float GetDeltaTime(sf::Clock& _clock);
	
	float Magnitude(sf::Vector2f& _vector);
}