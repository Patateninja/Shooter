#include "StateManager.hpp"

StateManager::StateManager()
{
	RscMana::Init();
	Win::Create(sf::VideoMode(1920,1080),"Shooter", sf::Style::Default);
	this->m_CurrentState = new Menu(this);
	this->m_CurrentState->Init();
}
StateManager::~StateManager()
{
	this->m_CurrentState->DeInit();
	this->m_CurrentState->Deletor();
	Win::Close();
}


void StateManager::Update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
	{
		Win::ToggleFullscreen();
	}

	this->m_CurrentState->Update();
}
void StateManager::Display()
{
	this->m_CurrentState->Display();
}