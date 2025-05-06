#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceManager.hpp"
#include "Shotgun.hpp"
#include "Player.hpp"
#include <iostream>

class StateManager;

class State
{
	protected:
		StateManager* m_StateManager = nullptr;
		ResourceManager* m_ResourceManager = nullptr;
		sf::Clock m_Clock;
		static bool m_GameResult;
	public :
		State() = default;
		~State() = default;

		virtual void Deletor() = 0;

		Window& Window();
		void ClearWindow();
		void Draw(sf::Drawable& _toDraw);
		void DisplayWindow();

		template <typename T>
		State* ChangeState();

		template<typename T>
		T& GetRsc(std::string _name);

		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Display() = 0;
		virtual void DeInit() = 0;
};

class Menu : public State
{
	private:

	public:
		Menu(StateManager* _stateManager, ResourceManager* m_ResourceManager = nullptr);
		~Menu();

		void Deletor() override;

		void Init() override;
		void Update() override;
		void Display() override;
		void DeInit() override;
};

class Game : public State
{
	private :
		Player m_Player;
		float m_SpawnTimer;
		float m_Deltatime;
	public:
		Game(StateManager* _stateManager, ResourceManager* m_ResourceManager = nullptr);
		~Game();

		void Deletor() override;

		void Init() override;
		void Update() override;
		void Display() override;
		void DeInit() override;
};

class EndGame : public State
{
	private:

	public:
		EndGame(StateManager* _stateManager, ResourceManager* m_ResourceManager = nullptr);
		~EndGame();

		void Deletor() override;

		void Init() override;
		void Update() override;
		void Display() override;
		void DeInit() override;
};

class Option : public State
{
	private:

	public:
		Option(StateManager* _stateManager, ResourceManager* m_ResourceManager = nullptr);
		~Option();

		void Deletor() override;

		void Init() override;
		void Update() override;
		void Display() override;
		void DeInit() override;
};

class Quit : public State
{
	private:

	public:
		Quit(StateManager* _stateManager, ResourceManager* m_ResourceManager = nullptr);
		~Quit();

		void Deletor() override;

		void Init() override;
		void Update() override;
		void Display() override;
		void DeInit() override;
};