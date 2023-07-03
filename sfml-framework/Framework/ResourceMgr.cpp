#include "stdafx.h"
#include "ResourceMgr.h"
#include "ErrorPrinter.h"

ResourceMgr::~ResourceMgr()
{
	UnloadAll();
}

void ResourceMgr::UnloadAll()
{
	for (auto pair : mapTexture)
	{
		delete pair.second;
	}
	mapTexture.clear();
	for (auto pair : mapFont)
	{
		delete pair.second;
	}
	mapFont.clear();
	for (auto pair : mapSoundBuffer)
	{
		delete pair.second;
	}
	mapSoundBuffer.clear();
	ERROR_PRINTER.isUnloadAll();
}

void ResourceMgr::Load(ResourceTypes t, const std::string path)
{
    //mapTexture["ID"] = new sf::Texture();
    //������ �־� ���, �޸� �� ��������
    switch (t)
	{
	case ResourceTypes::Texture:
	{
		auto it = mapTexture.find(path);
		//Ű�� ã�� �˻��Ѵ�.
		//���ͷ����Ϳ��� ->first Ű���� ->second���� �̷��� �ΰ����� ������

		//mapTexture.insert({ "ID", new sf::Texture() });
		 //Ű�� �˻��ϰ� ����
		if (mapTexture.end() == it)
		{
			auto texture = new sf::Texture();
			texture->loadFromFile(path);
			mapTexture.insert({ path, texture });
		}
	}
	break;
	case ResourceTypes::Font:
	{
		auto it = mapFont.find(path);
		if (mapFont.end() == it)
		{
			auto font = new sf::Font();
			font->loadFromFile(path);
			mapFont.insert({ path, font });
		}
	}
	break;
	case ResourceTypes::Sound:
	{
		auto it = mapSoundBuffer.find(path);
		if (mapSoundBuffer.end() == it)
		{
			auto sb = new sf::SoundBuffer();
			sb->loadFromFile(path);
			mapSoundBuffer.insert({ path, sb });
		}
	}
	break;
	}

   
}

void ResourceMgr::Load(const std::vector<std::tuple<ResourceTypes, std::string>>& array)
{
	for (const auto& tuple : array)
	{
		Load(std::get<0>(tuple), std::get<1>(tuple));
	}
}

void ResourceMgr::Unload(ResourceTypes t, const std::string path)
{
	switch (t)
	{
	case ResourceTypes::Texture:
	{
		auto it = mapTexture.find(path);
		if (it != mapTexture.end())
		{
			delete it->second;
			mapTexture.erase(it);
			ERROR_PRINTER.isUnload(path);
		}
	}
	break;
	case ResourceTypes::Font:
	{
		auto it = mapFont.find(path);
		if (it != mapFont.end())
		{
			delete it->second;
			mapFont.erase(it);
			ERROR_PRINTER.isUnload(path);
		}
	}
	break;
	case ResourceTypes::Sound:
	{
		auto it = mapSoundBuffer.find(path);
		if (it != mapSoundBuffer.end())
		{
			delete it->second;
			mapSoundBuffer.erase(it);
			ERROR_PRINTER.isUnload(path);
		}
	}
	break;
	}
}

void ResourceMgr::Unload(const std::vector<std::tuple<ResourceTypes, std::string>>& array)
{
	for (const auto& tuple : array)
	{
		Unload(std::get<0>(tuple), std::get<1>(tuple));
	}
}

sf::Texture* ResourceMgr::GetTexture(const std::string& id)
{
	auto it = mapTexture.find(id);
	if (it != mapTexture.end())
	{
		return it->second;
	}
	ERROR_PRINTER.GetFailCheck(id);
    return nullptr;
}

sf::Font* ResourceMgr::GetFont(const std::string& id)
{
	auto it = mapFont.find(id);
	if (it != mapFont.end())
	{
		return it->second;
	}
	ERROR_PRINTER.GetFailCheck(id);
    return nullptr;
}

sf::SoundBuffer* ResourceMgr::GetSoundBuffer(const std::string& id)
{
	auto it = mapSoundBuffer.find(id);
	if (it != mapSoundBuffer.end())
	{
		return it->second;
	}
	ERROR_PRINTER.GetFailCheck(id);
    return nullptr;
}
