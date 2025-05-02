#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class RSC
{
	virtual void foo() {};
};

template <typename T>
class Resource : public RSC
{
	private:
		T m_Rsc;
	public:
		Resource(std::string _path)
		{
			this->m_Rsc.loadFromFile(_path);
		}
		~Resource()
		{

		}

		T& GetRSC()
		{
			return this->m_Rsc;
		}
};

template <>
class Resource<sf::Music> : public RSC
{
	private:
		sf::Music m_Music;
	public:
		Resource(std::string _path)
		{
			this->m_Music.openFromFile(_path);
		}
		~Resource()
		{

		}

		sf::Music& GetRSC()
		{
			return this->m_Music;
		}
};

template <>
class Resource<sf::Sound> : public RSC
{
	private:
		sf::SoundBuffer m_Buffer;
		sf::Sound m_Sound;
	public:
		Resource(std::string _path)
		{
			this->m_Buffer.loadFromFile(_path);
			this->m_Sound.setBuffer(this->m_Buffer);
		}
		~Resource()
		{

		}

		sf::Sound& GetRsc()
		{
			return this->m_Sound;
		}
};