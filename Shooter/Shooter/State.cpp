#include "State.hpp"
#include "StateManager.hpp"

////////////////////////////////////////////////////////
#pragma region InitStatic

Muzzle State::m_Muzzle = Muzzle("Default Muzzle", 0, 1.f, 1.f, 1.f);
Grip State::m_Grip = Grip("Default Grip", 0, 1.f, 1.f, 1.f);
Stock State::m_Stock = Stock("Default Stock", 0, 1.f, 1.f, 1.f);
Magazine State::m_Magazine = Magazine("Default Magazine", 0, 0);
Armor State::m_Armor = Armor("None", 0, 0, 1.f);
AmmoStash State::m_AmmoStash = AmmoStash("Ammo Pouch", 0, 0);

int State::m_SfxVolume = 100;
int State::m_BgmVolume = 100;

int State::m_StageReached = 0;
int State::m_BestStage = 0;
#pragma endregion
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
	this->m_Text.setCharacterSize(120);

	this->m_Play = Button("", sf::Vector2f(25.f, 250.f), sf::Vector2f(400.f, 100.f), &RscMana::Get<sf::Texture>("PlayButton"));
	this->m_Option = Button("", sf::Vector2f(25.f, 400.f), sf::Vector2f(400.f, 100.f), &RscMana::Get<sf::Texture>("OptButton"));
	this->m_Quit = Button("", sf::Vector2f(25.f, 550.f), sf::Vector2f(400.f, 100.f), &RscMana::Get<sf::Texture>("ExitButton"));

	RscMana::SetSFXVolume(this->m_SfxVolume);
	RscMana::SetBGMVolume(this->m_BgmVolume);

	this->GetRsc<sf::Music>("Menu").play();
}
void Menu::Update()
{
	this->m_InputTimer += Time::GetDeltaTime();

	if (this->m_Play.Update(this->Window()))
	{
		this->m_InputTimer = 0.f;
		this->ChangeState<Upgrade>();
	}
	if (this->m_Option.Update(this->Window()))
	{
		this->m_InputTimer = 0.f;
		this->ChangeState<Option>();
	}
	if (this->m_Quit.Update(this->Window()))
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
	this->m_Option.Display(this->Window());
	this->m_Quit.Display(this->Window());

	this->DisplayWindow();
}
void Menu::DeInit()
{
	std::cout << "Menu DeInit" << std::endl;

	if(this->GetRsc<sf::Music>("Menu").getStatus() == sf::Sound::Status::Playing)
	{
		this->GetRsc<sf::Music>("Menu").stop();
	}
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
	this->m_Text.setCharacterSize(15);
	
	this->m_Player.Init(State::m_Muzzle, State::m_Grip, State::m_Magazine, State::m_Stock, State::m_Armor, State::m_AmmoStash);
	this->m_Cam.NewTarget(this->Window(), this->m_Player.GetPos(), this->m_Stage.GetMap().GetSize());

	this->m_Stage.SetNum(1);
	this->m_Stage.Init();

	this->m_RetryButon = Button("Retry", sf::Vector2f(1810.f,230.f), sf::Vector2f(70.f, 70.f), &RscMana::Get<sf::Texture>("Placeholder"));

	this->m_StageNum = CounterIcon(sf::Vector2f(1845.f, 10.f), sf::Vector2f(70.f, 70.f), &this->GetRsc<sf::Texture>("StageIcon"));
	this->m_Life = CounterIcon(sf::Vector2f(1845.f, 90.f), sf::Vector2f(70.f, 70.f), &this->GetRsc<sf::Texture>("HpIcon"));
	this->m_Vest = CounterIcon(sf::Vector2f(1845.f, 170.f), sf::Vector2f(70.f, 70.f), &this->GetRsc<sf::Texture>("VestIcon"));

	this->m_Coffee = Icon(sf::Vector2f(185.f, 70.f), sf::Vector2f(65.f, 65.f), &this->GetRsc<sf::Texture>("CoffeeIcon"));
	this->m_BMG50 = Icon(sf::Vector2f(260.f, 70.f), sf::Vector2f(65.f, 65.f), &this->GetRsc<sf::Texture>("BmgIcon"));

	this->Window().SetViewCenter(this->Window().GetDefaultView().GetCenter() - sf::Vector2f(Tile::GetSize() / 2.f, Tile::GetSize() / 2.f));

	State::m_StageReached = 0;

	this->GetRsc<sf::Music>("Game").play();
}
void Game::Update()
{
	this->m_InputTimer += Time::GetDeltaTime();

	if (this->m_Paused || this->m_PickupPopUpPause)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && this->m_InputTimer > 0.5f)
		{
			this->m_InputTimer = 0.f;
			this->m_Paused = !this->m_Paused;
		}

		if (this->m_BonusPopUp && !this->m_Paused)
		{
			this->m_BonusPopUp->Update(this->Window());
			this->m_PickupPopUpPause = true;

			if (this->m_BonusPopUp->GetToDelete())
			{
				delete this->m_BonusPopUp;
				this->m_BonusPopUp = nullptr;
				this->m_PickupPopUpPause = false;
			}
		}

		if (this->m_Paused)
		{
			this->m_PauseMenu.Update(this->Window(), this->m_Paused, *this->m_StateManager);
		}

		this->m_Player.SetTimer(0.f);
	}
	else
	{
		this->m_Cam.Update(this->Window());

		this->m_Text.setString(std::to_string(int(1 / Time::GetDeltaTime())) + " fps");
		this->m_Text.setPosition(this->Window().RelativePos(sf::Vector2f(1900.f - this->m_Text.getGlobalBounds().width, 0.f)));

		if (this->m_Player.GetMoving())
		{
			this->m_Cam.NewTarget(this->Window(), this->m_Player.GetPos(), this->m_Stage.GetMap().GetSize());
			if (this->m_RetryButon.Update(this->Window()))
			{
				this->m_Player.Die(this->m_Stage.GetEnemies(), this->m_Stage.GetMap(), this->m_Cam, this->Window());
				RscMana::Get<sf::Sound>("Player_Shot").play();
			}
		}
		else
		{
			this->m_ReloadMenu.Update(this->m_Player, this->m_Stage.GetEnemies(), this->Window());

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				this->m_Cam.NewTarget(this->Window(), this->Window().RelativePos(sf::Mouse::getPosition()), this->m_Stage.GetMap().GetSize());
			}
		}

		this->m_Player.Update(this->m_Stage.GetEnemies(), this->m_Stage.GetMap(), this->m_Cam, this->Window());
		this->m_Stage.Update(this->m_Player, this->m_Cam, this->m_BonusPopUp, this->Window());

		ProjList::Update(this->m_Stage.GetMap());

		if (this->m_Player.GetCoffeeEnabled())
		{
			this->m_Coffee.Update(this->Window());
		}
		if (this->m_Player.GetBmgEnabled())
		{
			this->m_BMG50.Update(this->Window());
		}
		this->m_StageNum.Update(this->Window(), this->m_Stage.GetNum());
		this->m_Life.Update(this->Window(), this->m_Player.GetHP());
		if (this->m_Player.GetVest() != 0)
		{
			this->m_Vest.Update(this->Window(), this->m_Player.GetVest());
		}

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
			this->m_PickupPopUpPause = true;

			if (this->m_BonusPopUp->GetToDelete())
			{
				delete this->m_BonusPopUp;
				this->m_BonusPopUp = nullptr;
				this->m_PickupPopUpPause = false;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && this->m_InputTimer > 0.2f)
		{
			this->m_InputTimer = 0.f;
			this->m_Paused = true;
		}

		if (this->m_Player.GetHP() == 0)
		{
			State::m_StageReached = this->m_Stage.GetNum();
			RscMana::Get<sf::Sound>("PlayerDeath").play();
			this->ChangeState<GameOver>();
		}
	}
}
void Game::Display()
{
	this->ClearWindow();

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

	if (this->m_Paused)
	{
		this->m_PauseMenu.Display(this->Window());
	}

	if (this->m_Player.GetCoffeeEnabled())
	{
		this->m_Coffee.Display(this->Window());
	}
	if (this->m_Player.GetBmgEnabled())
	{
		this->m_BMG50.Display(this->Window());
	}

	this->m_StageNum.Display(this->Window());
	this->m_Life.Display(this->Window());
	if (this->m_Player.GetVest() != 0)
	{
		this->m_Vest.Display(this->Window());
	}

	if (!this->m_Player.GetMoving())
	{
		this->m_ReloadMenu.Display(this->Window());

	}
	else if(this->m_Player.GetMoving())
	{
		this->m_RetryButon.Display(this->Window());
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

	if (this->GetRsc<sf::Music>("Game").getStatus() == sf::Sound::Status::Playing)
	{
		this->GetRsc<sf::Music>("Game").stop();
	}
}

#pragma endregion
////////////////////////////////////////////////////////
#pragma region GameOver

GameOver::GameOver(StateManager* _stateManager)
{
	std::cout << "GameOver Created" << std::endl;
	this->m_StateManager = _stateManager;
}
GameOver::~GameOver()
{
	std::cout << "GameOver Deleted" << std::endl;
}

void GameOver::Deletor()
{
	this->~GameOver();
}

void GameOver::Init()
{
	std::cout << "GameOver Init" << std::endl;
	this->Window().ResetView();
	this->m_Text.setFont(this->GetRsc<sf::Font>("Mono"));

	if (State::m_StageReached > State::m_BestStage)
	{
		State::m_BestStage = State::m_StageReached;
	}

	this->m_Text.setString("Game Over\nStage Reached : " + std::to_string(State::m_StageReached) + "\nBest Stage : " + std::to_string(State::m_BestStage));
	this->m_Text.setPosition(this->Window().GetViewCenter().x - (this->m_Text.getGlobalBounds().width * 2.f), 150.f);
	this->m_Text.setCharacterSize(120);

	this->m_ToMenu = Button("", sf::Vector2f(250.f, 800.f), sf::Vector2f(300.f, 75.f), &RscMana::Get<sf::Texture>("MenuButton"));
	this->m_ToShop = Button("", sf::Vector2f(1420.f, 800.f), sf::Vector2f(300.f, 75.f), &RscMana::Get<sf::Texture>("ShopButton"));

	this->GetRsc<sf::Music>("GameOverMusic").play();
}
void GameOver::Update()
{
	this->m_InputTimer += Time::GetDeltaTime();

	if (this->m_ToMenu.Update(this->Window()))
	{
		this->m_InputTimer = 0.f;
		this->ChangeState<Menu>();
	}
	if (this->m_ToShop.Update(this->Window()))
	{
		this->m_InputTimer = 0.f;
		this->ChangeState<Upgrade>();
	}
}
void GameOver::Display()
{
	this->ClearWindow();

	this->Draw(this->m_Text);
	this->m_ToMenu.Display(this->Window());
	this->m_ToShop.Display(this->Window());

	this->DisplayWindow();
}
void GameOver::DeInit()
{
	std::cout << "GameOver DeInit" << std::endl;

	if (this->GetRsc<sf::Music>("GameOverMusic").getStatus() == sf::Sound::Status::Playing)
	{
		this->GetRsc<sf::Music>("GameOverMusic").stop();
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
	this->m_Shop.Init(Level::GetLvl(), State::GetMuzzle(), State::m_Grip, State::m_Stock, State::m_Magazine, State::m_Armor, State::m_AmmoStash);
	
	this->m_Text.setString("Armory");
	this->m_Text.setCharacterSize(60);
	this->m_Text.setFont(this->GetRsc<sf::Font>("Mono"));

	this->m_DelayRect.setSize(sf::Vector2f(1920.f, 1080.f));
	this->m_DelayRect.setPosition(sf::Vector2f(0.f, 0.f));
	this->m_DelayRect.setTexture(&this->GetRsc<sf::Texture>("Placeholder"));

	this->m_Play = Button("", sf::Vector2f(1595.f, 980.f), sf::Vector2f(300.f, 75.f), &RscMana::Get<sf::Texture>("PlayButton"));
	this->m_Menu = Button("", sf::Vector2f(25.f, 980.f), sf::Vector2f(300.f, 75.f), &RscMana::Get<sf::Texture>("MenuButton"));

	this->GetRsc<sf::Music>("Armory").play();
}

void Upgrade::Update()
{	
	this->m_InputTimer += Time::GetDeltaTime();

	if (!this->m_ShopActive && this->m_InputTimer > 0.5f)
	{
		this->m_ShopActive = true;
	}

	if (this->m_ShopActive)
	{
		this->m_Shop.Update(this->Window());
	}

	State::m_Muzzle = this->m_Shop.GetMuzzle();
	State::m_Grip = this->m_Shop.GetGrip();
	State::m_Stock = this->m_Shop.GetStock();
	State::m_Magazine = this->m_Shop.GetMagazine();
	State::m_Armor = this->m_Shop.GetArmor();
	State::m_AmmoStash = this->m_Shop.GetAmmoStash();

	if (this->m_Play.Update(this->Window()))
	{
		this->m_InputTimer = 0.f;
		this->ChangeState<Game>();
	}
	if (this->m_Menu.Update(this->Window()))
	{
		this->m_InputTimer = 0.f;
		this->ChangeState<Menu>();
	}
}
void Upgrade::Display()
{
	this->ClearWindow();

	if (this->m_ShopActive)
	{
		this->Draw(this->m_Text);
		this->m_Shop.Display(this->Window());

		this->m_Play.Display(this->Window());
		this->m_Menu.Display(this->Window());
	}
	else
	{
		this->Draw(this->m_DelayRect);
	}

	this->DisplayWindow();
}
void Upgrade::DeInit()
{
	std::cout << "Upgrade DeInit" << std::endl;

	if (this->GetRsc<sf::Music>("Armory").getStatus() == sf::Sound::Status::Playing)
	{
		this->GetRsc<sf::Music>("Armory").stop();
	}
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

	this->GetRsc<sf::Music>("Option").play();

	this->m_Fullscreen = this->Window().GetFullscreen();

	this->m_SFX = Slider(sf::Vector2f(300.f, 250.f), sf::Vector2f(700.f, 25.f), 0);
	this->m_BGM = Slider(sf::Vector2f(300.f, 450.f), sf::Vector2f(700.f, 25.f), 0);
	this->m_FullscreenCheckbox = Checkbox("", sf::Vector2f(200.f, 700.f), sf::Vector2f(75.f, 75.f), &RscMana::Get<sf::Texture>("Checkbox"), this->m_Fullscreen);
	this->m_Menu = Button("", sf::Vector2f(25.f, 960.f), sf::Vector2f(400, 100.f), &RscMana::Get<sf::Texture>("MenuButton"));
}
void Option::Update()
{
	this->m_InputTimer += Time::GetDeltaTime();

	this->m_SFX.Update(this->Window(), this->m_SfxVolume);
	RscMana::SetSFXVolume(this->m_SfxVolume);

	this->m_BGM.Update(this->Window(), this->m_BgmVolume);
	RscMana::SetBGMVolume(this->m_BgmVolume);

	if (this->m_Menu.Update(this->Window()))
	{
		this->ChangeState<Menu>();
	}

	this->m_Fullscreen = this->Window().GetFullscreen();

	if (this->m_InputTimer > 0.2f)
	{
		this->m_FullscreenCheckbox.Update(this->Window(), this->m_Fullscreen);
	}

	if (this->Window().GetFullscreen() != this->m_Fullscreen)
	{
		this->Window().SetFullScreen(this->m_Fullscreen);
		this->m_InputTimer = 0;
	}
}
void Option::Display()
{
	this->ClearWindow();

	this->m_Text.setCharacterSize(60);
	this->m_Text.setString("Settings");
	this->m_Text.setPosition(10.f, 5.f);
	this->Draw(this->m_Text);

	this->m_Menu.Display(this->Window());
	
	this->m_Text.setCharacterSize(30);
	this->m_Text.setString("Fullscreen");
	this->m_Text.setPosition(300.f, 720.f);
	this->Draw(this->m_Text);
	this->m_FullscreenCheckbox.Display(this->Window());
	
	this->m_Text.setCharacterSize(30);
	this->m_Text.setString("SFX");
	this->m_Text.setPosition(200.f, 230.f);
	this->Draw(this->m_Text);
	this->m_SFX.Display(this->Window());

	this->m_Text.setCharacterSize(30);
	this->m_Text.setString("BGM");
	this->m_Text.setPosition(200.f, 430.f);
	this->Draw(this->m_Text);
	this->m_BGM.Display(this->Window());

	this->DisplayWindow();
}
void Option::DeInit()
{
	std::cout << "Option DeInit" << std::endl;

	if (this->GetRsc<sf::Music>("Option").getStatus() == sf::Sound::Status::Playing)
	{
		this->GetRsc<sf::Music>("Option").stop();
	}
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