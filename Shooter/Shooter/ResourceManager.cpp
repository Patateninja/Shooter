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
	std::string path = "..\\Resources\\";

	//Fonts
	this->Add<sf::Font>("Ubuntu", path + "Fonts\\Ubuntu.ttf");

	//Textures
	this->Add<sf::Texture>("Red_Shell", path + "Textures\\Red_Shell.png");

	//SFX
	this->Add<sf::Sound>("Shot", path + "SFX\\Shot.ogg");

	//BGM
	this->Add<sf::Music>("Bogus", path + "BGM\\Bogus.ogg");
}