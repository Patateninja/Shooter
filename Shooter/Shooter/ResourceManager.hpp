#pragma once
#include <unordered_map>
#include "Resource.hpp"

class ResourceManager
{
	private :
		std::unordered_map<std::string, RSC*> m_RessourcesStorage;
	
	public :
		ResourceManager() = default;
		~ResourceManager();

		void Init();
		inline std::unordered_map<std::string, RSC*>& GetMap() { return this->m_RessourcesStorage; };

		template <typename T>
		void Add(std::string _name, std::string _path)
		{
			Resource<T>* resource = new Resource<T>(_path);
			this->m_RessourcesStorage.insert(std::make_pair(_name, resource));
		}

		template <typename T>
		T& Get(std::string _name)
		{
			return dynamic_cast<Resource<T>*>(this->m_RessourcesStorage[_name])->GetRSC();
		}

		void SetSFXVolume(int _volume);
		void SetBGMVolume(int _volume);
};


namespace RscMana
{
	void Init();

	void AddWrapped(std::string _name, RSC* _r);

	template <typename T>
	void Add(std::string _name, std::string _path)
	{
		Resource<T>* resource = new Resource<T>(_path);
		RscMana::AddWrapped(_name, resource);
	};

	RSC* GetWrapped(std::string _name);

	template <typename T>
	T& Get(std::string _name)
	{
		return dynamic_cast<Resource<T>*>(GetWrapped(_name))->GetRSC();
	}

	void SetBGMVolume(int _volume);
	void SetSFXVolume(int _volume);
}