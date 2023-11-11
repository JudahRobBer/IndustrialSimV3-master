#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string.h>
#include <fstream>
#include <unordered_map>
#include <exception>



//class used for textures, fonts, sounds, music
template<class T>
class AssetLoader
{
public:

	AssetLoader()
	{
	}
	~AssetLoader()
	{
	}

	void load(std::string key, std::string fileName)
	{
		T temp;

		if (!temp.loadFromFile(fileName))
			throw std::runtime_error("AssetLoader failed to load: " + fileName);

		assets[key] = temp;

	}

	T& get(std::string key)
	{
		if (!assets.empty())
			return assets.at(key);
	}

private:
	std::unordered_map<std::string, T> assets;
};

