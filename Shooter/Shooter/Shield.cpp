#include "Shield.hpp"

Shield::Shield(sf::Vector2f _pos)
{
	this->m_Rect.setSize(sf::Vector2f(5.f, 50.f));
	this->m_Rect.setOrigin(-30.f, 25.f);
	this->m_Rect.setPosition(_pos);
}

void Shield::Udpate(bool _active, sf::Vector2f _pos, float _angle)
{
	this->SetActive(_active);
	this->SetPos(_pos);
	this->SetAngle(_angle);

	if (this->m_Active)
	{
		this->CheckContact();
	}
}
void Shield::Display(Window& _window)
{
	_window.Draw(this->m_Rect);
}

void Shield::CheckContact()
{
	for (const std::shared_ptr<Projectile>& proj : ProjList::GetList())
	{
		if (proj->GetTeam() == PLAYER && this->m_Rect.getGlobalBounds().intersects(proj->GetHitbox()) && proj->GetType() != PIERCING)
		{
			proj->SetToDestroy(true);
		}
	}
}