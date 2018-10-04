#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>
#include <SFML/Graphics.hpp>

namespace Resources{

class ResourceManager{
    public:
        ResourceManager();

        void addFont   (const std::string &fontName);
        void addTexture(const std::string &textureName);

        const sf::Font    &getFont   (const std::string &fontName) const;
        const sf::Texture &getTexture(const std::string &textureName) const;
    private:
        std::map <std::string, sf::Font>    fonts;
        std::map <std::string, sf::Texture> textures;
};

}

#endif // RESOURCEMANAGER_H
