#include "State.hpp"
#include "StateManager.hpp"

#include "Shell.hpp"

////////////////////////////////////////////////////////

bool State::m_GameResult = true;

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && Tools::GetDeltaTime(this->m_Clock) > 0.2)
	{
		this->ChangeState<Option>();
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->m_SpawnTimer > 1.f)
	{
		this->m_SpawnTimer = 0.f;
		
		switch (rand() % 4)
		{
			case 0 : 
			{
				BirdShot shell;
				shell.Shot(this->m_List);
				break;
			}
			case 1 :
			{
				BuckShot shell;
				shell.Shot(this->m_List);
				break;
			}
			case 2 :
			{
				Incendiary shell;
				shell.Shot(this->m_List);
				break;
			}
			case 3 :
			{
				Slug shell;
				shell.Shot(this->m_List);
				break;
			}
		}
		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11) && this->m_SpawnTimer > 0.3f)
	{
		this->m_SpawnTimer = 0.f;
		this->m_StateManager->GetWindow().ToggleFullscreen();
	}

	this->m_List.Update(this->m_Deltatime);
}
void Game::Display()
{
	this->ClearWindow();

	this->m_List.Display(this->m_StateManager->GetWindow());

	sf::VertexArray lines(sf::Lines, 2);
	lines[0].position = sf::Vector2f(0.f, 0.f);
	lines[0].color = sf::Color::Red;
	lines[1].position = Tools::AngleToVector(800.f, Tools::VectorsToAngle(sf::Vector2f(1.f, 0.f), sf::Vector2f(sf::Mouse::getPosition())));
	lines[1].color = sf::Color::Red;
	this->Draw(lines);

	sf::Font font;
	font.loadFromFile("..\\Resources\\Font\\Ubuntu.ttf");
	sf::Text text(std::to_string(this->m_List.size()), font);
	this->Draw(text);

	sf::Text fps(std::to_string(int(1 / this->m_Deltatime)) + "fps", font);
	fps.setPosition(sf::Vector2f(1900.f - fps.getGlobalBounds().width, 0.f));
	this->Draw(fps);

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