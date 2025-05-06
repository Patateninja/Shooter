#include "State.hpp"
#include "StateManager.hpp"

////////////////////////////////////////////////////////
#pragma region State

bool State::m_GameResult = true;

Window& State::Window()
{
	return this->m_StateManager->GetWindow();
}
void State::ClearWindow()
{
	this->m_StateManager->ClearWindow();
}
void State::Draw(sf::Drawable& _toDraw)
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
T& State::GetRsc(std::string _name)
{
	return RscMana::Get<T>(_name);
}

Window& State::Window()
{
	return this->m_StateManager->GetWindow();
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
	this->m_Text.setFont(this->GetRsc<sf::Font>("Ubuntu"));
}
void Menu::Update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && Tools::GetDeltaTime(this->m_Clock) > 0.2)
	{
		this->m_Clock.restart();
		this->ChangeState<Game>();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && Tools::GetDeltaTime(this->m_Clock) > 0.2)
	{
		this->ChangeState<Quit>();
	}
}
void Menu::Display()
{
	this->ClearWindow();

	this->m_Text.setString("Menu, Press Enter to continue");
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
	this->m_Clock = sf::Clock();

	this->m_Deltatime = 0;
	this->m_SpawnTimer = 0;

	font.loadFromFile("..\\Resources\\Font\\Ubuntu.ttf");
	text.setFont(font);
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
	this->m_Text.setFont(this->GetRsc<sf::Font>("Ubuntu"));

	this->GetRsc<sf::Music>("Bogus").play();
}
void Game::Update()
{
	this->m_Deltatime = Tools::GetDeltaTime(this->m_Clock);
	this->m_Clock.restart();

	this->m_Text.setString(std::to_string(ProjList::Size()) + " / " + std::to_string(int(1 / this->m_Deltatime)) + "fps");
	this->m_Text.setPosition(sf::Vector2f(1900.f - this->m_Text.getGlobalBounds().width, 0.f));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
	{
		this->ChangeState<EndGame>();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->GetRsc<sf::Sound>("Shot").play();
	}

	this->m_Player.Update(this->m_Deltatime);
	ProjList::Update(this->m_Deltatime);
}
void Game::Display()
{
	this->ClearWindow();

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
#pragma region  EndGame

EndGame::EndGame(StateManager* _stateManager)
{
	std::cout << "EndGame Created" << std::endl;
	this->m_StateManager = _stateManager;
}
EndGame::~EndGame()
{
	std::cout << "EndGame Deleted" << std::endl;
}

void EndGame::Deletor()
{
	this->~EndGame();
}

void EndGame::Init()
{
	std::cout << "EndGame Init" << std::endl;
}
void EndGame::Update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		this->ChangeState<Menu>();
	}
}
void EndGame::Display()
{
	this->ClearWindow();

	this->DisplayWindow();
}
void EndGame::DeInit()
{
	std::cout << "EndGame DeInit" << std::endl;
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
	this->m_Text.setFont(this->GetRsc<sf::Font>("Ubuntu"));
}
void Option::Update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
	{
		this->ChangeState<Menu>();
	}
}
void Option::Display()
{
	this->ClearWindow();

	this->m_Text.setString("Option\nPress Backspace to return to Menu");
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