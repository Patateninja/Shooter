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
	this->Add<sf::Font>("Ubuntu", path + "Fonts\\Ubuntu.ttf");
	this->Add<sf::Font>("Mono", path + "Fonts\\Mono_Regular.ttf");
	this->Add<sf::Font>("Pixel", path + "Fonts\\pixelatedczs.ttf");

	//Textures
	this->Add<sf::Texture>("PlayButton", path + "Textures\\Button_Play.png");
	this->Add<sf::Texture>("OptButton", path + "Textures\\Button_Option.png");
	this->Add<sf::Texture>("ExitButton", path + "Textures\\Button_Exit.png");
	this->Add<sf::Texture>("MenuButton", path + "Textures\\Button_Menu.png");
	this->Add<sf::Texture>("ShopButton", path + "Textures\\Button_Shop.png");
	this->Add<sf::Texture>("ResumeButton", path + "Textures\\Button_Resume.png");
	this->Add<sf::Texture>("ReadyButton", path + "Textures\\Button_Ready.png");
	

	this->Add<sf::Texture>("Ammo", path + "Textures\\Ammo.png");
	this->Add<sf::Texture>("Bird", path + "Textures\\Green_Shell.png");
	this->Add<sf::Texture>("Buck", path + "Textures\\Red_Shell.png");
	this->Add<sf::Texture>("Dragon", path + "Textures\\Blue_Shell.png");
	this->Add<sf::Texture>("Slug", path + "Textures\\Yellow_Shell.png");
	this->Add<sf::Texture>("Bmg", path + "Textures\\Not_a_Shell.png");

	this->Add<sf::Texture>("FloorTile", path + "Textures\\Floor.png");
	this->Add<sf::Texture>("Table", path + "Textures\\Table.png");
	this->Add<sf::Texture>("Barrel", path + "Textures\\Barrel.png");

	this->Add<sf::Texture>("HpIcon", path + "Textures\\HpIcon.png");
	this->Add<sf::Texture>("StageIcon", path + "Textures\\StageIcon.png");
	this->Add<sf::Texture>("VestIcon", path + "Textures\\Vest.png");
	this->Add<sf::Texture>("BmgIcon", path + "Textures\\BMG_Icon.png");
	this->Add<sf::Texture>("CoffeeIcon", path + "Textures\\Coffee_Icon.png");

	this->Add<sf::Texture>("Checkbox", path + "Textures\\CheckBox.png");

	this->Add<sf::Texture>("Placeholder", path + "Textures\\Placeholder.png");

	//SFX
	this->Add<sf::Sound>("Player_Shot", path + "SFX\\Player_Shot.ogg");
	this->Add<sf::Sound>("Player_Step", path + "SFX\\Walking.ogg");

	this->Add<sf::Sound>("Button_Hover", path + "SFX\\Shot.ogg");
	this->Add<sf::Sound>("Button_Click", path + "SFX\\Shot.ogg");
	this->Add<sf::Sound>("Slider_Blip", path + "SFX\\Shot.ogg");

	this->Add<sf::Sound>("Shop_Equip", path + "SFX\\Shot.ogg");

	this->Add<sf::Sound>("Reload", path + "SFX\\Reload.ogg");
	this->Add<sf::Sound>("Reload_Denied", path + "SFX\\No_Ammo.ogg");
	this->Add<sf::Sound>("Ready", path + "SFX\\Shot.ogg");
	this->Add<sf::Sound>("EmptyMag", path + "SFX\\Empty_Mag.ogg");

	this->Add<sf::Sound>("Enemy_Shot", path + "SFX\\Shot.ogg");

	this->Add<sf::Sound>("PlayerDeath", path + "SFX\\Game_Over.ogg");
	this->Add<sf::Sound>("Hurt_Enemies", path + "SFX\\Shot.ogg");
	this->Add<sf::Sound>("Death_Enemies", path + "SFX\\Shot.ogg");
	this->Add<sf::Sound>("Hurt_dog", path + "SFX\\Shot.ogg");
	this->Add<sf::Sound>("Death_dog", path + "SFX\\Shot.ogg");

	this->Add<sf::Sound>("CrateOpen", path + "SFX\\Open_Crate.ogg");
	this->Add<sf::Sound>("EquipementSelected", path + "SFX\\Equip.ogg");

	this->Add<sf::Sound>("Next_Stage_Popup", path + "SFX\\Shot.ogg");
	this->Add<sf::Sound>("GameOver", path + "SFX\\Shot.ogg");

	this->Add<sf::Sound>("ButtonClicked", path + "SFX\\Button_Clicked.ogg");
	this->Add<sf::Sound>("ButtonHover", path + "SFX\\Button_Hover.ogg");

	//BGM
	this->Add<sf::Music>("Menu", path + "BGM\\Main_Menu.ogg");
	this->Add<sf::Music>("Option", path + "BGM\\Option.ogg");
	this->Add<sf::Music>("Armory", path + "BGM\\Shop.ogg");
	this->Add<sf::Music>("Game", path + "BGM\\Game.ogg");
	this->Add<sf::Music>("GameOverMusic", path + "BGM\\Game_Over.ogg");
}

void ResourceManager::SetSFXVolume(int _volume)
{
	for (std::unordered_map<std::string, RSC*>::iterator iterator = this->m_RessourcesStorage.begin(); iterator != this->m_RessourcesStorage.end(); ++iterator)
	{
		if (iterator->second->IsSound())
		{
			iterator->second->SetVolume(_volume);
		}
	}
}

void ResourceManager::SetBGMVolume(int _volume)
{
	for (std::unordered_map<std::string, RSC*>::iterator iterator = this->m_RessourcesStorage.begin(); iterator != this->m_RessourcesStorage.end(); ++iterator)
	{
		if (iterator->second->IsMusic())
		{
			iterator->second->SetVolume(_volume);
		}
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