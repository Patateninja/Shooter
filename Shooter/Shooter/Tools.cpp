#include "Tools.hpp"

//////////////////////////////////////////////////
#pragma region Tools

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
	sf::Vector2f vect(1.f, 0.f);
	return Tools::VectorsToAngle(vect, _vect);
}
sf::Vector2f Tools::AngleToVector(float const _len, float const _angle)
{
	return sf::Vector2f(std::cos(_angle) * _len, std::sin(_angle) * _len);
}

float Tools::Magnitude(sf::Vector2f const _vect)
{
	return float(std::sqrt(std::pow(_vect.x, 2.0) + std::pow(_vect.y, 2.0)));
}
sf::Vector2f Tools::Normalize(sf::Vector2f const _vect)
{
	if (_vect.x == 0.f && _vect.y == 0.f)
	{
		return sf::Vector2f(0.f, 0.f);
	}
	else
	{
		return sf::Vector2f(_vect.x / Tools::Magnitude(_vect), _vect.y / Tools::Magnitude(_vect));
	}
}

float Tools::RadToDeg(float _rad)
{
	return (_rad * (180 / PI));
}
float Tools::DegToRad(float _deg)
{
	return (_deg * (PI / 180));
}

int Tools::Random(int _max, int _min = 0)
{
	return Tools::Min<int,int,int>(_max,(rand() % (_max + 1)) + _min);
}

float Tools::Distance(sf::Vector2f _vect1, sf::Vector2f _vect2)
{
	return float(std::sqrt(std::pow(_vect2.x - _vect1.x, 2) + std::pow(_vect2.y - _vect1.y, 2)));
}

int Tools::ToClosestMultiple(int _val, int _multiple)
{
	if (_val < 0)
	{
		_multiple = -_multiple;
	}
	float valHalf = static_cast<float>(_val) + (static_cast<float>(_multiple) * .5f);
	int ret = (static_cast<int>(valHalf) / _multiple) * _multiple;
	return ret;
}

float Tools::ToPercent(float _float)
{
	return ((_float - 1) * 100);
}

int Tools::ToRoundPercent(float _float)
{
	return int(std::round((_float - 1) * 100));
}

sf::Vector2f Tools::RectCenter(const sf::FloatRect& _rect)
{
	return sf::Vector2f((_rect.left + _rect.width / 2.f) , (_rect.top + _rect.height / 2.f));
}

bool Tools::CircleCollision(const sf::FloatRect& _circlehitbox1, const sf::FloatRect& _circlehitbox2)
{
	return std::abs(Tools::Distance(Tools::RectCenter(_circlehitbox1), Tools::RectCenter(_circlehitbox2))) <= (_circlehitbox1.width / 2.f + _circlehitbox2.width / 2.f);
}

#pragma endregion
//////////////////////////////////////////////////

namespace Time
{
	sf::Clock time;
	float deltaTime;

	void Init()
	{
		Time::time = sf::Clock();
		Time::deltaTime = 0.f;
	}

	void UpdateTime()
	{
		Time::deltaTime = Tools::GetDeltaTime(Time::time);
	}

	float GetDeltaTime()
	{
		return Time::deltaTime;
	}

	sf::Time Restart()
	{
		return Time::time.restart();
	}
}

//////////////////////////////////////////////////