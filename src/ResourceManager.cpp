#include "ResourceManager.h"

namespace Resources{

ResourceManager::ResourceManager(){
    addFont("arial.ttf");

    addTexture("brush.png");
    addTexture("circle.png");
    addTexture("clearScreen.png");
    addTexture("copyColor.png");
    addTexture("colorPicker.png");
    addTexture("eraser.png");
    addTexture("on.png");
    addTexture("off.png");
    addTexture("rectangle.png");
}

void ResourceManager::addFont(const std::string &fontName){
    sf::Font font;
    font.loadFromFile("resources/fonts/" + fontName);
    fonts[fontName] = font;
}

void ResourceManager::addTexture(const std::string &textureName){
    sf::Texture texture;
    texture.loadFromFile("resources/textures/" + textureName);
    textures[textureName] = texture;
}

const sf::Font &ResourceManager::getFont(const std::string &fontName) const{
    return fonts.at(fontName);
}

const sf::Texture &ResourceManager::getTexture(const std::string &textureName) const{
    return textures.at(textureName);
}

}
