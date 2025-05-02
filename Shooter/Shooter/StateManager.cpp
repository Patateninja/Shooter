#include "StateManager.hpp"

StateManager::StateManager(ResourceManager* _resourceManager)
{
	this->m_Window.Create(sf::VideoMode(1920,1080),"Shooter", sf::Style::Fullscreen);
	this->m_ResourceManager = _resourceManager;
	this->m_CurrentState = new Menu(this, _resourceManager);
	this->m_CurrentState->Init();
}
StateManager::~StateManager()
{
	this->m_CurrentState->DeInit();
	delete this->m_CurrentState;
	this->m_Window.Close();
}

void StateManager::ClearWindow()
{
	this->m_Window.Clear();
}
void StateManager::Draw(sf::Drawable& _toDraw)
{
	this->m_Window.Draw(_toDraw);
}
void StateManager::DisplayWindow()
{
	this->m_Window.Display();
}

void StateManager::Update()
{
	this->m_CurrentState->Update();
}
void StateManager::Display()
{
	this->m_CurrentState->Display();
}