#pragma once
#include "SFML/Graphics.hpp"
#include <cmath>
#include <ctime>
#include <cstdlib>

#define PI 3.14159

namespace Tools
{
	float GetDeltaTime(sf::Clock& _clock);
	
	float VectorsToAngle(sf::Vector2f const _vect1, sf::Vector2f const _vect2);

	float VectorToAngle(sf::Vector2f const _vect);

	sf::Vector2f AngleToVector(float const _len, float const _angmle);

	float Magnitude(sf::Vector2f const _vector);

	sf::Vector2f Normalize(sf::Vector2f _vect);

	float RadToDeg(float _rad);

	float DegToRad(float _deg);

	int Random(int _max, int _min);
}

namespace Time
{
	void Init();
	float GetDeltaTime();
	sf::Time Restart();
}