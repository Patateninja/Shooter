#pragma once
#include "Player.hpp"
#include "Enemy.hpp"
#include "Stage.hpp"
#include "Camera.hpp" 
#include "Shop.hpp"
#include "BonusPopUp.hpp"
#include "LoadMenu.hpp"
#include "PauseMenu.hpp"

class StateManager;

class State
{
	protected :
		StateManager* m_StateManager = nullptr;
		sf::Text m_Text;
		float m_InputTimer = 0;

		static Muzzle m_Muzzle;
		static Grip m_Grip;
		static Stock m_Stock;
		static Magazine m_Magazine;
		static Armor m_Armor;
		static AmmoStash m_AmmoStash;
		
	public :
		State() = default;
		~State() = default;

		virtual void Deletor() = 0;

		Window& Window();
		void ClearWindow();
		void Draw(const sf::Drawable& _toDraw);
		void DisplayWindow();

		template <typename T>
		State* ChangeState();

		template<typename T>
		T& GetRsc(const std::string& _name);

		static Muzzle& GetMuzzle() { return State::m_Muzzle; }
		static Grip& GetGrip() { return State::m_Grip; }
		static Stock& GetStock() { return State::m_Stock; }
		static Magazine& GetMagazine() { return State::m_Magazine; }
		static Armor& GetArmor() { return State::m_Armor; }
		static AmmoStash& GetAmmoStash() { return State::m_AmmoStash; }

		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Display() = 0;
		virtual void DeInit() = 0;
};

class Menu : public State
{
	private :
		Button m_Play;
		Button m_Option;
		Button m_Quit;

	public :
		Menu(StateManager* _stateManager);
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
		ReloadMenu m_ReloadMenu;
		PauseMenu m_PauseMenu;
		Player m_Player;
		Stage m_Stage;
		Camera m_Cam;
		PopUp* m_StagePopUp = nullptr;
		BonusPopUp* m_BonusPopUp = nullptr;
		bool m_Paused = false;
		bool m_PickupPopUpPause = false;

	public :
		Game(StateManager* _stateManager);
		~Game();

		void Deletor() override;

		void Init() override;
		void Update() override;
		void Display() override;
		void DeInit() override;
};

class GameOver : public State
{
	private:
		Button m_ToMenu;
		Button m_ToShop;

	public:
		GameOver(StateManager* _stateManager);
		~GameOver();

		void Deletor() override;

		void Init() override;
		void Update() override;
		void Display() override;
		void DeInit() override;
};

class Upgrade : public State
{
	private :
		sf::RectangleShape m_DelayRect;
		Shop m_Shop;
		Button m_Menu;
		Button m_Play;
		int m_PlayerLevel = 0;
		bool m_ShopActive = false;

	public :
		Upgrade(StateManager* _stateManager);
		~Upgrade();

		void Deletor() override;

		void Init() override;
		void Update() override;
		void Display() override;
		void DeInit() override;
};

class Option : public State
{
	private :

	public :
		Option(StateManager* _stateManager);
		~Option();

		void Deletor() override;

		void Init() override;
		void Update() override;
		void Display() override;
		void DeInit() override;
};

class Quit : public State
{
	private :

	public :
		Quit(StateManager* _stateManager);
		~Quit();

		void Deletor() override;

		void Init() override;
		void Update() override;
		void Display() override;
		void DeInit() override;
};