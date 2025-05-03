#pragma once
#include <map>
#include "Resource.hpp"

class ResourceManager
{
	private:
		std::map<std::string, RSC*> m_RessourcesStorage;
	public:
		ResourceManager();
		~ResourceManager();

		void Init();

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
};