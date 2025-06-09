#include "PauseMenu.hpp"

#include "StateManager.hpp"

void PauseMenu::Update(Window& _window, bool& _pause, StateManager& _stateManager)
{
	this->m_Resume.SetPosition(_window.RelativePos(sf::Vector2f(785.f, 150.f)));
	if (this->m_Resume.Update(_window))
	{
		_pause = false;
	}

	this->m_ToShop.SetPosition(_window.RelativePos(sf::Vector2f(785.f, 250.f)));
	if (this->m_ToShop.Update(_window))
	{
		_stateManager.ChangeState<Upgrade>();
	}

	this->m_ToMenu.SetPosition(_window.RelativePos(sf::Vector2f(785.f, 350.f)));
	if (this->m_ToMenu.Update(_window))
	{
		_stateManager.ChangeState<Menu>();
	}

	this->m_ToDesktop.SetPosition(_window.RelativePos(sf::Vector2f(785.f, 450.f)));
	if (this->m_ToDesktop.Update(_window))
	{
		_stateManager.ChangeState<Quit>();
	}
}

void PauseMenu::Display(Window& _window)
{
	this->m_Resume.Display(_window);
	this->m_ToShop.Display(_window);
	this->m_ToMenu.Display(_window);
	this->m_ToDesktop.Display(_window);
}