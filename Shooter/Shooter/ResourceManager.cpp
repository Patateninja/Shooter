#include "ResourceManager.hpp"

ResourceManager::~ResourceManager()
{
	while (!this->m_RessourcesStorage.empty())
	{
		this->m_RessourcesStorage.begin()->second->Deletor();
		this->m_RessourcesStorage.erase(this->m_RessourcesStorage.begin());
	}
}

void ResourceManager::Init()
{
	std::string path = "..\\Resources\\";

	//Fonts
	this->Add<sf::Font>("Mono", path + "Fonts\\Mono_Regular.ttf");

	//Textures
	this->Add<sf::Texture>("Red_Shell", path + "Textures\\Red_Shell.png");
	this->Add<sf::Texture>("Placeholder", path + "Textures\\Placeholder.png");

	//SFX
	this->Add<sf::Sound>("Shot", path + "SFX\\Shot.ogg");

	//BGM
	this->Add<sf::Music>("Bogus", path + "BGM\\Bogus.ogg");
}

void ResourceManager::SetSFXVolume(int _volume)
{
	for (std::unordered_map<std::string, RSC*>::iterator iterator = this->m_RessourcesStorage.begin(); iterator != this->m_RessourcesStorage.end(); ++iterator)
	{
		iterator->second->SetVolume(_volume);
	}
}

void ResourceManager::SetBGMVolume(int _volume)
{
	for (std::unordered_map<std::string, RSC*>::iterator iterator = this->m_RessourcesStorage.begin(); iterator != this->m_RessourcesStorage.end(); ++iterator)
	{
		iterator->second->SetVolume(_volume);
	}
}


namespace RscMana
{
	ResourceManager rscm;

	void Init()
	{
		RscMana::rscm.Init();
	}

	void AddWrapped(std::string _name, RSC* _rsc) {
		RscMana::rscm.GetMap().insert(std::make_pair(_name, _rsc));
	}

	RSC* GetWrapped(std::string _name)
	{
		return RscMana::rscm.GetMap()[_name];
	}
	
	void SetBGMVolume(int _volume)
	{
		rscm.SetBGMVolume(_volume);
	}

	void SetSFXVolume(int _volume)
	{
		rscm.SetSFXVolume(_volume);
	}
}