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

Menu::Menu(StateManager* _stateManager, ResourceManager* _resourceManager)
{
	std::cout << "Menu Created" << std::endl;
	this->m_StateManager = _stateManager;
	this->m_ResourceManager = _resourceManager;
}
Menu::~Menu()
{
	std::cout << "Menu Deleted" << std::endl;
}

void Menu::Init()
{
	std::cout << "Menu Init" << std::endl;
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
}
Game::~Game()
{
	std::cout << "Game Deleted" << std::endl;
}

void Game::Init()
{
	std::cout << "Game Init" << std::endl;
}
void Game::Update()
{
	this->m_Deltatime = Tools::GetDeltaTime(this->m_Clock);
	this->m_Clock.restart();
	this->m_SpawnTimer += this->m_Deltatime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
	{
		this->ChangeState<EndGame>();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && this->m_SpawnTimer > 0.3f)
	{
		this->m_SpawnTimer = 0.f;
		this->m_Shotgun.Load(1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && this->m_SpawnTimer > 0.3f)
	{
		this->m_SpawnTimer = 0.f;
		this->m_Shotgun.Load(2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && this->m_SpawnTimer > 0.3f)
	{
		this->m_SpawnTimer = 0.f;
		this->m_Shotgun.Load(3);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && this->m_SpawnTimer > 0.3f)
	{
		this->m_SpawnTimer = 0.f;
		this->m_Shotgun.Load(4);
	}

	this->m_Player.Update(this->m_Deltatime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->m_SpawnTimer > 1.f)
	{
		this->m_SpawnTimer = 0.f;
		this->m_Shotgun.Shoot(this->m_List, this->m_Player.GetPos());
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11) && this->m_SpawnTimer > 0.3f)
	{
		this->m_SpawnTimer = 0.f;
		this->m_StateManager->GetWindow().ToggleFullscreen();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		this->m_Player.Respawn();
	}

	this->m_List.Update(this->m_Deltatime);
}
void Game::Display()
{
	this->ClearWindow();

	this->m_List.Display(this->Window());
	this->m_Player.Display(this->Window());
	this->m_Shotgun.DisplayMagazine(this->Window());

	sf::Font font;
	font.loadFromFile("..\\Resources\\Font\\Ubuntu.ttf");
	sf::Text text("Projectile : " + std::to_string(this->m_List.size()) + " " + std::to_string(int(1 / this->m_Deltatime)) + "fps", font);
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