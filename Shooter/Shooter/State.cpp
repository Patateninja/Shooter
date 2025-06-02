#include "State.hpp"
#include "StateManager.hpp"

////////////////////////////////////////////////////////

Muzzle State::m_Muzzle = Muzzle("Default Muzzle", 0, 1.f, 1.f, 1.f);
Grip State::m_Grip = Grip("Default Grip", 0, 1.f, 1.f, 1.f);
Stock State::m_Stock = Stock("Default Stock", 0, 1.f, 1.f, 1.f);
Magazine State::m_Magazine = Magazine("Default Magazine", 0, 0);
Armor State::m_Armor = Armor("None", 0, 0, 1.f);
AmmoStash State::m_AmmoStash = AmmoStash("Ammo Pouch", 0, 0);

////////////////////////////////////////////////////////
#pragma region State

Window& State::Window()
{
	return this->m_StateManager->GetWindow();
}
void State::ClearWindow()
{
	this->Window().Clear();
}
void State::Draw(const sf::Drawable& _toDraw)
{
	this->m_StateManager->Draw(_toDraw);
}
void State::DisplayWindow()
{
	this->m_StateManager->DisplayWindow();
}

template<typename T>
State* State::ChangeState()
{
	return this->m_StateManager->ChangeState<T>();
}

template<typename T>
T& State::GetRsc(const std::string& _name)
{
	return RscMana::Get<T>(_name);
}

#pragma endregion
////////////////////////////////////////////////////////
#pragma region Menu

Menu::Menu(StateManager* _stateManager)
{
	std::cout << "Menu Created" << std::endl;
	this->m_StateManager = _stateManager;
}
Menu::~Menu()
{
	std::cout << "Menu Deleted" << std::endl;
}

void Menu::Deletor()
{
	this->~Menu();
}

void Menu::Init()
{
	std::cout << "Menu Init" << std::endl;
	this->Window().ResetView();
	this->m_Text.setFont(this->GetRsc<sf::Font>("Mono"));
	this->m_Text.setString("BREACH");
	this->m_Text.setPosition(10.f, 5.f);
	this->m_Text.setCharacterSize(120.f);

	this->m_Play = Button("Play", sf::Vector2f(25.f, 200.f), sf::Vector2f(200.f, 75.f), &RscMana::Get<sf::Texture>("Placeholder"));
	this->m_Quit = Button("Quit", sf::Vector2f(25.f, 300.f), sf::Vector2f(200.f, 75.f), &RscMana::Get<sf::Texture>("Placeholder"));
}
void Menu::Update()
{
	this->m_InputTimer += Time::GetDeltaTime();

	if (this->m_Play.Update(this->Window(),0))
	{
		this->m_InputTimer = 0.f;
		this->ChangeState<Upgrade>();
	}
	if (this->m_Quit.Update(this->Window(),0))
	{
		this->m_InputTimer = 0.f;
		this->ChangeState<Quit>();
	}
}
void Menu::Display()
{
	this->ClearWindow();

	this->Draw(this->m_Text);
	this->m_Play.Display(this->Window());
	this->m_Quit.Display(this->Window());

	this->DisplayWindow();
}
void Menu::DeInit()
{
	std::cout << "Menu DeInit" << std::endl;
}

#pragma endregion
////////////////////////////////////////////////////////
#pragma region Game

Game::Game(StateManager* _stateManager)
{
	std::cout << "Game Created" << std::endl;
	this->m_StateManager = _stateManager;
}
Game::~Game()
{
	std::cout << "Game Deleted" << std::endl;
}

void Game::Deletor()
{
	this->~Game();
}

void Game::Init()
{
	std::cout << "Game Init" << std::endl;
	this->m_Text.setFont(this->GetRsc<sf::Font>("Mono"));
	//this->GetRsc<sf::Music>("Bogus").play();
	
	this->m_Player.Init(State::m_Muzzle, State::m_Grip, State::m_Magazine, State::m_Stock, State::m_Armor, State::m_AmmoStash);
	this->m_Cam.NewTarget(this->Window(), this->m_Player.GetPos(), this->m_Stage.GetMap().GetSize());

	this->m_Stage.SetNum(1);
	this->m_Stage.Init();

	this->Window().SetViewCenter(this->Window().GetDefaultView().GetCenter() - sf::Vector2f(Tile::GetSize() / 2.f, Tile::GetSize() / 2.f));
}
void Game::Update()
{
	this->m_InputTimer += Time::GetDeltaTime();

	if (this->m_Paused)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && this->m_InputTimer > 0.2f)
		{
			this->m_InputTimer = 0.f;
			this->ChangeState<Menu>();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->m_InputTimer > 0.2f)
		{
			this->m_InputTimer = 0.f;
			this->m_Paused = false;
		}
	}
	else
	{
		this->m_Text.setString("Stage : " + std::to_string(this->m_Stage.GetNum()) + " / " + std::to_string(this->m_Player.GetHP()) + " Live(s) / " + std::to_string(int(1 / Time::GetDeltaTime())) + " fps");
		this->m_Text.setPosition(this->Window().RelativePos(sf::Vector2f(1900.f - this->m_Text.getGlobalBounds().width, 0.f)));

		this->m_Player.Update(this->m_Stage.GetEnemies(), this->m_Stage.GetMap(), this->m_Cam, this->Window());
		this->m_Stage.Update(this->m_Player, this->m_Cam, this->m_BonusPopUp ,this->Window());
		ProjList::Update(this->m_Stage.GetMap());

		this->m_Cam.Update(this->Window());

		if (this->m_Stage.GetMoveOn())
		{
			if (this->m_StagePopUp == nullptr)
			{
				this->m_StagePopUp = new PopUp(sf::Vector2f(590.f, 340.f), sf::Vector2f(800.f, 400.f), "Stage Cleared\nPress Enter to continue");
			}
			else
			{
				this->m_StagePopUp->Update(this->Window());
			}
		}
		else
		{
			if (this->m_StagePopUp)
			{
				delete this->m_StagePopUp;
				this->m_StagePopUp = nullptr;
			}
		}






		if (this->m_BonusPopUp)
		{
			this->m_BonusPopUp->Update(this->Window());

			if (this->m_BonusPopUp->GetToDelete())
			{
				delete this->m_BonusPopUp;
				this->m_BonusPopUp = nullptr;
			}
		}






		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && this->m_InputTimer > 0.2f)
		{
			this->m_InputTimer = 0.f;
			this->m_Paused = true;
		}
		if (this->m_Player.GetHP() == 0)
		{
			this->ChangeState<Upgrade>();
		}
	}
}
void Game::Display()
{
	this->ClearWindow();

	if (this->m_Paused)
	{
		this->m_Stage.Display(this->Window());
		ProjList::Display(this->Window());
		this->m_Player.Display(this->Window());
		this->Draw(this->m_Text);
	}
	else
	{
		this->m_Stage.Display(this->Window());
		ProjList::Display(this->Window());
		this->m_Player.Display(this->Window());
		this->Draw(this->m_Text);

		if (this->m_StagePopUp)
		{
			this->m_StagePopUp->Display(this->Window());
		}

		if (this->m_BonusPopUp)
		{
			this->m_BonusPopUp->Display(this->Window());
		}
	}

	this->DisplayWindow();
}
void Game::DeInit()
{
	std::cout << "Game DeInit" << std::endl;

	if (this->m_StagePopUp)
	{
		delete this->m_StagePopUp;
	}
	if (this->m_BonusPopUp)
	{
		delete this->m_BonusPopUp;
	}
}

#pragma endregion
////////////////////////////////////////////////////////
#pragma region Upgrade

Upgrade::Upgrade(StateManager* _stateManager)
{
	std::cout << "Upgrade Created" << std::endl;
	this->m_StateManager = _stateManager;
}
Upgrade::~Upgrade()
{
	std::cout << "Upgrade Deleted" << std::endl;
}

void Upgrade::Deletor()
{
	this->~Upgrade();
}

void Upgrade::Init()
{
	std::cout << "Upgrade Init" << std::endl;
	this->Window().ResetView();
	this->m_Shop = Shop(Level::GetLvl(), State::m_Muzzle, State::m_Grip, State::m_Stock, State::m_Magazine,	State::m_Armor, State::m_AmmoStash);
	this->m_Text.setFont(this->GetRsc<sf::Font>("Mono"));

	this->m_Play = Button("Start", sf::Vector2f(1695.f, 980.f), sf::Vector2f(200.f, 75.f), &RscMana::Get<sf::Texture>("Placeholder"));
	this->m_Menu = Button("Menu", sf::Vector2f(25.f, 980.f), sf::Vector2f(200.f, 75.f), &RscMana::Get<sf::Texture>("Placeholder"));
}
void Upgrade::Update()
{
	this->m_InputTimer += Time::GetDeltaTime();
	this->m_Text.setString("Upgrade Menu\nPress Enter to launch a new game\nPress Escape to go back to Menu");

	this->m_Shop.Update(this->Window());

	State::m_Muzzle = this->m_Shop.GetMuzzle();
	State::m_Grip = this->m_Shop.GetGrip();
	State::m_Stock = this->m_Shop.GetStock();
	State::m_Magazine = this->m_Shop.GetMagazine();
	State::m_Armor = this->m_Shop.GetArmor();
	State::m_AmmoStash = this->m_Shop.GetAmmoStash();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->m_InputTimer > 0.2f)
	{
		this->m_InputTimer = 0.f;
		this->ChangeState<Game>();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && this->m_InputTimer > 0.2f)
	{
		this->m_InputTimer = 0.f;
		this->ChangeState<Menu>();
	}

	if (this->m_Play.Update(this->Window(), 0))
	{
		this->m_InputTimer = 0.f;
		this->ChangeState<Game>();
	}
	if (this->m_Menu.Update(this->Window(), 0))
	{
		this->m_InputTimer = 0.f;
		this->ChangeState<Menu>();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add) && this->m_InputTimer > 0.2f)
	{
		this->m_InputTimer = 0.f;
		if (this->m_PlayerLevel < 35)
		{
			Level::GainXP(28510);
			this->m_PlayerLevel = Level::GetLvl();
			this->m_Shop.SetLevel(this->m_PlayerLevel);
		}
	}
}
void Upgrade::Display()
{
	this->ClearWindow();

	this->Draw(this->m_Text);
	this->m_Shop.Display(this->Window());

	this->m_Play.Display(this->Window());
	this->m_Menu.Display(this->Window());

	this->DisplayWindow();
}
void Upgrade::DeInit()
{
	std::cout << "Upgrade DeInit" << std::endl;
}

#pragma endregion
////////////////////////////////////////////////////////
#pragma region Option

Option::Option(StateManager* _stateManager)
{
	std::cout << "Option Created" << std::endl;
	this->m_StateManager = _stateManager;
}
Option::~Option()
{
	std::cout << "Option Deleted" << std::endl;
}

void Option::Deletor()
{
	this->~Option();
}

void Option::Init()
{
	std::cout << "Option Init" << std::endl;
	this->Window().ResetView();
	this->m_Text.setFont(this->GetRsc<sf::Font>("Mono"));
}
void Option::Update()
{
	this->m_Text.setString("Option\nPress Backspace to return to Menu");

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
	{
		this->ChangeState<Menu>();
	}
}
void Option::Display()
{
	this->ClearWindow();

	this->Draw(this->m_Text);

	this->DisplayWindow();
}
void Option::DeInit()
{
	std::cout << "Option DeInit" << std::endl;
}

#pragma endregion
////////////////////////////////////////////////////////
#pragma region Quit

Quit::Quit(StateManager* _stateManager)
{
	std::cout << "Quit Created" << std::endl;
	this->m_StateManager = _stateManager;
}
Quit::~Quit()
{
	std::cout << "Quit Deleted" << std::endl;
}

void Quit::Deletor()
{
	this->~Quit();
}

void Quit::Init()
{
	std::cout << "Quit Init" << std::endl;
	this->Window().ResetView();
}
void Quit::Update()
{
	this->Window().Close();
}
void Quit::Display()
{

}
void Quit::DeInit()
{
	std::cout << "Quit DeInit" << std::endl;
}

#pragma endregion
////////////////////////////////////////////////////////