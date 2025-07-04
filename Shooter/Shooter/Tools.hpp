#pragma once
#include "SFML/Graphics.hpp"
#include "Colors.hpp"
#include <cmath>
#include <ctime>
#include <cstdlib>

constexpr float PI = 3.14159f;

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

	int Random(int _max, int _min = 0);

	float Distance(sf::Vector2f _vect1, sf::Vector2f _vect2);

	int ToClosestMultiple(int _val, int _multiple);

	float ToPercent(float _float);
	
	int ToRoundPercent(float _float);

	template<typename T, typename U, typename V>
	V Min(T _val1, U _val2)
	{
		return V(_val1 < _val2 ? _val1 : _val2);
	}

	template<typename T, typename U, typename V>
	V Max(T _val1, U _val2)
	{
		return V(_val1 > _val2 ? _val1 : _val2);
	}

	template<typename T>
	int Sign(T _val)
	{
		return (_val < 0 ? -1 : 1);
	}

	sf::Vector2f RectCenter(const sf::FloatRect& _rect);

	bool CircleCollision(const sf::FloatRect& _circlehitbox1, const sf::FloatRect& _circlehitbox2);
}

namespace Time
{
	void Init();
	void UpdateTime();
	float GetDeltaTime();
	sf::Time Restart();
}