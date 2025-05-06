#include "State.hpp"
#include "StateManager.hpp"

////////////////////////////////////////////////////////

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
	return this->m_ResourceManager->Get<T>(_name);
}

////////////////////////////////////////////////////////
sf::Font font;
sf::Text text;

Menu::Menu(StateManager* _stateManager, ResourceManager* _resourceManager)
{
	std::cout << "Menu Created" << std::endl;
	this->m_StateManager = _stateManager;
	this->m_ResourceManager = _resourceManager;

	font.loadFromFile("..\\Resources\\Font\\Ubuntu.ttf");
	text.setFont(font);
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

	text.setString("Menu, Press Enter To Play");
	text.setPosition(sf::Vector2f(900.f - text.getGlobalBounds().width, 540.f));
	this->Draw(text);

	this->DisplayWindow();
}
void Menu::DeInit()
{
	std::cout << "Menu DeInit" << std::endl;
}

////////////////////////////////////////////////////////

Game::Game(StateManager* _stateManager, ResourceManager* _resourceManager)
{
	std::cout << "Game Created" << std::endl;
	this->m_StateManager = _stateManager;
	this->m_ResourceManager = _resourceManager;
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
}
void Game::Update()
{
	this->m_Deltatime = Tools::GetDeltaTime(this->m_Clock);
	this->m_Clock.restart();

	this->m_Player.Update(this->m_Deltatime);
	ProjList::ListUpdate(this->m_Deltatime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11) && this->m_SpawnTimer > 0.3f)
	{
		this->m_SpawnTimer = 0.f;
		this->m_StateManager->GetWindow().ToggleFullscreen();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
	{
		this->ChangeState<EndGame>();
	}
}
void Game::Display()
{
	this->ClearWindow();

	ProjList::ListDisplay(this->Window());
	this->m_Player.Display(this->Window());

	text.setString("Projectile : " + std::to_string(ProjList::ListSize()) + " / " + std::to_string(int(1 / this->m_Deltatime)) + "fps");
	text.setPosition(sf::Vector2f(1900.f - text.getGlobalBounds().width, 0.f));
	this->Draw(text);

	this->DisplayWindow();
}
void Game::DeInit()
{
	std::cout << "Game DeInit" << std::endl;
}

////////////////////////////////////////////////////////

EndGame::EndGame(StateManager* _stateManager, ResourceManager* _resourceManager)
{
	std::cout << "EndGame Created" << std::endl;
	this->m_StateManager = _stateManager;
	this->m_ResourceManager = _resourceManager;
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

////////////////////////////////////////////////////////

Option::Option(StateManager* _stateManager, ResourceManager* _resourceManager)
{
	std::cout << "Option Created" << std::endl;
	this->m_StateManager = _stateManager;
	this->m_ResourceManager = _resourceManager;
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

	sf::Text text("Option\nPress Backspace to return to Menu", this->GetRsc<sf::Font>("Ubuntu"));
	this->Draw(text);

	this->DisplayWindow();
}
void Option::DeInit()
{
	std::cout << "Option DeInit" << std::endl;
}

////////////////////////////////////////////////////////

Quit::Quit(StateManager* _stateManager, ResourceManager* _resourceManager)
{
	std::cout << "Quit Created" << std::endl;
	this->m_StateManager = _stateManager;
	this->m_ResourceManager = nullptr;
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
	this->m_StateManager->GetWindow().Close();
}
void Quit::Display()
{

}
void Quit::DeInit()
{
	std::cout << "Quit DeInit" << std::endl;
}

////////////////////////////////////////////////////////