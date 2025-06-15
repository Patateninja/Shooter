#include "StateManager.hpp"

////////////////////////////////////////////////////////

StateManager::StateManager()
{
	RscMana::Init();
	Time::Init();
	SaveSystem::Load("save.data", Level::GetXp(), this->m_CurrentState->GetMuzzle(), this->m_CurrentState->GetGrip(), this->m_CurrentState->GetStock(), this->m_CurrentState->GetMagazine(), this->m_CurrentState->GetArmor(), this->m_CurrentState->GetAmmoStash(), this->m_CurrentState->GetSFXVolume(), this->m_CurrentState->GetBGMVolume(), this->m_CurrentState->GetBestStage());


	this->m_CurrentState = new Menu(this);
	this->m_CurrentState->Init();
	this->m_InputTimer = 0;

	while (Level::CalculateLvL());
}
StateManager::~StateManager()
{
	SaveSystem::Save("save.data", Level::GetXp(), this->m_CurrentState->GetMuzzle(), this->m_CurrentState->GetGrip(), this->m_CurrentState->GetStock(), this->m_CurrentState->GetMagazine(), this->m_CurrentState->GetArmor(), this->m_CurrentState->GetAmmoStash(), this->m_CurrentState->GetSFXVolume(), this->m_CurrentState->GetBGMVolume(), this->m_CurrentState->GetBestStage());

	this->m_CurrentState->DeInit();
	this->m_CurrentState->Deletor();
	this->m_Window.Close();
}

void StateManager::ClearWindow()
{
	this->m_Window.Clear();
}
void StateManager::Draw(const sf::Drawable& _toDraw)
{
	this->m_Window.Draw(_toDraw);
}
void StateManager::DisplayWindow()
{
	this->m_Window.Display();
}


void StateManager::Update()
{
	Time::UpdateTime();
	Time::Restart();

	this->m_InputTimer += Time::GetDeltaTime();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11) && this->m_InputTimer > 0.5f)
	{
		this->m_InputTimer = 0;;
		this->m_Window.ToggleFullscreen();
	}

	this->m_CurrentState->Update();
}
void StateManager::Display()
{
	this->m_CurrentState->Display();
}

////////////////////////////////////////////////////////