#include "AssetManager.h"

std::map<std::string, sf::Texture> AssetManager::textures;
std::map<std::string, sf::Font> AssetManager::fonts;
std::map<std::string, sf::SoundBuffer> AssetManager::soundBuffers;


sf::Texture& AssetManager::RequestTexture(std::string assetName)
{
    // Find the texture in the textures map
    auto pairFound = textures.find(assetName);

    if (pairFound != textures.end())
    {
        // We found an existing texture! Use it
        return pairFound->second; // the value in the key-value pair
    }
    else
    {
        // If not there, create a new texture
        sf::Texture& newTexture = textures[assetName];
        newTexture.loadFromFile(assetName);
        return newTexture;
    }


}

sf::Font& AssetManager::RequestFont(std::string assetName)
{
    // Find the font in the fonts map
    auto pairFound = fonts.find(assetName);

    if (pairFound != fonts.end())
    {
        // We found an existing texture! Use it
        return pairFound->second; // the value in the key-value pair
    }
    else
    {
        // If not there, create a new font
        sf::Font& newFont = fonts[assetName];
        newFont.loadFromFile(assetName);
        return newFont;
    }


}

sf::SoundBuffer& AssetManager::RequestSoundBuffer(std::string assetName)
{
    // Find the sound buffer in the sound buffers map
    auto pairFound = soundBuffers.find(assetName);

    if (pairFound != soundBuffers.end())
    {
        // We found an existing texture! Use it
        return pairFound->second; // the value in the key-value pair
    }
    else
    {
        // If not there, create a new sound buffer
        sf::SoundBuffer& newSoundBuffer = soundBuffers[assetName];
        newSoundBuffer.loadFromFile(assetName);
        return newSoundBuffer;
    }


}

void AssetManager::DestroyAllAssets()
{
    textures.clear();
    fonts.clear();
    soundBuffers.clear();
}
