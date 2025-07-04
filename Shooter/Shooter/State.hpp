#pragma once
#include "Stage.hpp"
#include "Shop.hpp"
#include "LoadMenu.hpp"
#include "PauseMenu.hpp"
#include "Slider.hpp"
#include "Checkbox.hpp"
#include "CounterIcon.hpp"

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

		static int m_SfxVolume;
		static int m_BgmVolume;

		static int m_StageReached;
		static int m_BestStage;
		
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

		static int& GetSFXVolume() { return State::m_SfxVolume; }
		static int& GetBGMVolume() { return State::m_BgmVolume; }

		static int& GetBestStage() { return State::m_BestStage; }

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
		~Menu() = default;

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
		Button m_RetryButon;
		CounterIcon m_StageNum;
		CounterIcon m_Life;
		CounterIcon m_Vest;
		Icon m_Coffee;
		Icon m_BMG50;
		Camera m_Cam;
		PopUp* m_StageClearPopUp = nullptr;
		PopUp* m_NextStagePopUp = nullptr;
		BonusPopUp* m_BonusPopUp = nullptr;
		float m_PopTimer = 0.f;
		bool m_Paused = false;
		bool m_PickupPopUpPause = false;

	public :
		Game(StateManager* _stateManager);
		~Game() = default;

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
		~GameOver() = default;

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
		~Upgrade() = default;

		void Deletor() override;

		void Init() override;
		void Update() override;
		void Display() override;
		void DeInit() override;
};

class Option : public State
{
	private :
		Button m_Menu;
		Checkbox m_FullscreenCheckbox;
		Slider m_SFX;
		Slider m_BGM;
		bool m_Fullscreen = false;

	public :
		Option(StateManager* _stateManager);
		~Option() = default;

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
		~Quit() = default;

		void Deletor() override;

		void Init() override;
		void Update() override;
		void Display() override;
		void DeInit() override;
};