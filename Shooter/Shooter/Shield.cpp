#include "Shield.hpp"

Shield::Shield(sf::Vector2f _pos)
{
	this->m_Rect.setSize(sf::Vector2f(5.f, 50.f));
	this->m_Rect.setOrigin(-15.f, 25.f);
	this->m_Rect.setPosition(_pos);
	this->m_Rect.setTexture(&RscMana::Get<sf::Texture>("Shield"));
}

void Shield::Udpate(bool _active, sf::Vector2f _pos, float _angle)
{
	this->SetActive(_active);
	this->SetPos(_pos);
	this->m_TargetAngle = _angle;

	if (this->m_Active)
	{
		this->CheckContact();

		if (this->m_Rect.getRotation() != this->m_TargetAngle)
		{
			float angle = (this->m_TargetAngle - this->m_Rect.getRotation());
			if (angle < -135)
			{
				angle += 360.f;
			}
			float rotation = Tools::Sign(angle) * Tools::Min<float, float, float>(std::abs(angle) * Time::GetDeltaTime() * 2.5f, std::abs(angle));

			this->m_Rect.setRotation(this->m_Rect.getRotation() + rotation);
		}
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