#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;

class TextureManager{
    static unordered_map<string, sf::Texture> textures;
    static void LoadTexture(string textureName);
public:
    static sf::Texture& GetTexture(string textureName);
    static void Clear();
};

unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string textureName) {
    string path = "images/";
    path +=textureName + ".png";

    textures[textureName].loadFromFile(path);

}

sf::Texture& TextureManager::GetTexture(string textureName){
    if(textures.find(textureName) == textures.end()){
        LoadTexture(textureName);
    }
    return textures[textureName];
}

void TextureManager::Clear() {
    textures.clear();
}