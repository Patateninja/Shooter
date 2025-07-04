#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>

class RSC
{
	public :
		virtual void Deletor() {}

		virtual void SetVolume(int _volume) {} //Find better way to do it
		virtual bool IsMusic() { return false; } //Find better way to do it
		virtual bool IsSound() { return false; } //Find better way to do it
};

template <typename T>
class Resource : public RSC
{
	private :
		T m_Rsc;

	public :
		Resource(std::string _path)
		{
			this->m_Rsc.loadFromFile(_path);
		}
		~Resource() = default;

		void Deletor() override
		{
			this->~Resource();
		}

		T& GetRSC()
		{
			return this->m_Rsc;
		}

		bool IsMusic() override { return false; } //Find better way to do it
		bool IsSound() override { return false; } //Find better way to do it
};

template <>
class Resource<sf::Music> : public RSC
{
	private :
		sf::Music m_Music;

	public :
		Resource(std::string _path)
		{
			this->m_Music.openFromFile(_path);
			this->m_Music.setLoop(true);
		}
		~Resource() = default;

		void Deletor() override
		{
			this->~Resource();
		}

		void SetVolume(int _volume) override
		{
			this->m_Music.setVolume(float(_volume));
		}

		sf::Music& GetRSC()
		{
			return this->m_Music;
		}

		bool IsMusic() override { return true; } //Find better way to do it
		bool IsSound() override { return false; } //Find better way to do it
};

template <>
class Resource<sf::Sound> : public RSC
{
	private :
		sf::SoundBuffer m_Buffer;
		sf::Sound m_Sound;

	public :
		Resource(std::string _path)
		{
			this->m_Buffer.loadFromFile(_path);
			this->m_Sound.setBuffer(this->m_Buffer);
		}
		~Resource() = default;

		void Deletor() override
		{
			this->~Resource();
		}

		void SetVolume(int _volume) override
		{
			this->m_Sound.setVolume(float(_volume));
		}

		sf::Sound& GetRSC()
		{
			return this->m_Sound;
		}

		bool IsMusic() override { return false; } //Find better way to do it
		bool IsSound() override { return true; } //Find better way to do it
};