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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && this->m_InputTimer > 0.2f)
	{
		this->m_InputTimer = 0.f;
		this->ChangeState<Game>();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && this->m_InputTimer > 0.2f)
	{
		this->m_InputTimer = 0.f;
		this->ChangeState<Quit>();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11) && this->m_InputTimer > 0.5f)
	{
		this->m_InputTimer = 0.f;
		this->Window().ToggleFullscreen();
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
	this->m_EnemyList = EnemyList();
	this->m_MapTexture.create(Tile::GetSize() * 20, Tile::GetSize() * 20);
	this->m_Map = TileMap(sf::Vector2i(20, 20));
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
	this->m_Map.Generate(this->m_MapTexture);
	this->m_MapSprite.setTexture(this->m_MapTexture.getTexture());
	this->m_MapSprite.setPosition(-Tile::GetSize() / 2.f, - Tile::GetSize() / 2.f);

	this->m_EnemyList.Add<Baseliner>(sf::Vector2f(64.f, 640.f));
	this->m_EnemyList.Add<Tank>(sf::Vector2f(960.f, 1152.f));
	this->m_EnemyList.Add<Swarmer>(sf::Vector2f(1152.f, 832.f));
	this->m_EnemyList.Add<Ranged>(sf::Vector2f(512.f, 1024.f));
}
void Game::Update()
{
	this->m_InputTimer += Time::GetDeltaTime();

	this->m_Text.setString(std::to_string(this->m_Player.GetHP()) + " Live(s) / Projectiles : " + std::to_string(ProjList::Size()) + " / " + std::to_string(int(1 / Time::GetDeltaTime())) + " fps");
	this->m_Text.setPosition(this->Window().RelativePos(sf::Vector2f(1900.f - this->m_Text.getGlobalBounds().width, 0.f)));

	this->m_Player.Update(this->m_EnemyList, this->Window());
	ProjList::Update(this->m_Map);
	this->Window().SetViewCenter(this->m_Player.GetPos());

	this->m_EnemyList.Update(this->m_Player.GetPos(), this->m_Map);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && this->m_InputTimer > 0.2f)
	{
		this->m_InputTimer = 0.f;
		this->ChangeState<Menu>();
	}
}
void Game::Display()
{
	this->ClearWindow();

	this->Draw(this->m_MapSprite);

	ProjList::Display(this->Window());
	this->m_EnemyList.Display(this->Window());
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
	this->Window().ResetView();
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
	this->Window().ResetView();
	this->m_Text.setFont(this->GetRsc<sf::Font>("Mono"));
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