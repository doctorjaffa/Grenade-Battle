#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>

class AssetManager
{

// Public functions/data
public:

	// Request assets from asset folder
	static sf::Texture& RequestTexture(std::string assetName);
	static sf::Font& RequestFont(std::string assetName);
	static sf::SoundBuffer& RequestSoundBuffer(std::string assetName);

	// Clear all assets 
	static void DestroyAllAssets();

// Private functions/data
private:

	// Maps that contain these assets 
	static std::map<std::string, sf::Texture> textures;
	static std::map<std::string, sf::Font> fonts;
	static std::map<std::string, sf::SoundBuffer> soundBuffers;

};

