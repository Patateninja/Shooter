#include "ResourceManager.hpp"

ResourceManager::ResourceManager()
{

}
ResourceManager::~ResourceManager()
{
	this->m_RessourcesStorage.clear();
}

void ResourceManager::Init()
{
	this->Add<sf::Font>("Ubuntu", "..\\Resources\\Font\\Ubuntu.ttf");
}