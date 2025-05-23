#include "State.hpp"
#include "StateManager.hpp"

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
}
void Menu::Update()
{
	this->m_InputTimer += Time::GetDeltaTime();
	this->m_Text.setString("Main Menu\nPress Enter to continue\nPress Escape to exit game");

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->m_InputTimer > 0.2f)
	{
		this->m_InputTimer = 0.f;
		this->ChangeState<Upgrade>();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && this->m_InputTimer > 0.2f)
	{
		this->m_InputTimer = 0.f;
		this->ChangeState<Quit>();
	}
}
void Menu::Display()
{
	this->ClearWindow();

	this->Draw(this->m_Text);

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
	this->Window().ResetView();
	this->m_Text.setFont(this->GetRsc<sf::Font>("Mono"));
	//this->GetRsc<sf::Music>("Bogus").play();
	
	this->m_Stage.SetNum(3);
	this->m_Stage.Init();
}
void Game::Update()
{
	this->m_InputTimer += Time::GetDeltaTime();

	this->m_Text.setString("Stage : " + std::to_string(this->m_Stage.GetNum()) + " / " + std::to_string(this->m_Player.GetHP()) + " Live(s) / " + std::to_string(int(1 / Time::GetDeltaTime())) + " fps");
	this->m_Text.setPosition(this->Window().RelativePos(sf::Vector2f(1900.f - this->m_Text.getGlobalBounds().width, 0.f)));

	this->m_Player.Update(this->m_Stage.GetEnemies(), this->m_Stage.GetMap(), this->Window());
	this->m_Stage.Update(this->m_Player);
	ProjList::Update(this->m_Stage.GetMap());

	this->m_Cam.Update(this->Window(), this->m_Player.GetPos(), this->m_Stage.GetMap().GetSize());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && this->m_InputTimer > 0.2f)
	{
		this->m_InputTimer = 0.f;
		this->ChangeState<Menu>();
	}
	if (this->m_Player.GetHP() == 0)
	{
		this->ChangeState<Upgrade>();
	}
}
void Game::Display()
{
	this->ClearWindow();

	this->m_Stage.Display(this->Window());

	ProjList::Display(this->Window());
	this->m_Player.Display(this->Window());

	this->Draw(this->m_Text);

	this->DisplayWindow();
}
void Game::DeInit()
{
	std::cout << "Game DeInit" << std::endl;
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
	this->m_Text.setFont(this->GetRsc<sf::Font>("Mono"));
}
void Upgrade::Update()
{
	this->m_InputTimer += Time::GetDeltaTime();
	this->m_Text.setString("Upgrade Menu\nPress Enter to launch a new game\nPress Escape to go back to Menu");

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
}
void Upgrade::Display()
{
	this->ClearWindow();

	this->Draw(this->m_Text);

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