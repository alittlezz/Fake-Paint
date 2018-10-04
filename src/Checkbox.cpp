#include "Checkbox.h"

#include <Resources.h>

Checkbox::Checkbox(const int &x, const int &y, const Types &_type, const std::string &_text, const double &scale){
    icon.setPosition(sf::Vector2f(x + _text.size() * 8, y));
    icon.setTexture(Resources::resourceManager.getTexture("on.png"));
    icon.scale(sf::Vector2f(scale / 2, scale / 2));

    text.setString(_text);
    text.setPosition(sf::Vector2f(x - 10, y + 5));
    text.setFont(Resources::resourceManager.getFont("arial.ttf"));
    text.setCharacterSize(17);
    text.setColor(sf::Color::Black);

    type = _type;
    isOn = true;
}

void Checkbox::switchFill(){
    if(isOn){
        isOn = false;
        icon.setTexture(Resources::resourceManager.getTexture("off.png"));
    }else{
        isOn = true;
        icon.setTexture(Resources::resourceManager.getTexture("on.png"));
    }
}

void Checkbox::draw(sf::RenderWindow &window) const{
    window.draw(icon);
    window.draw(text);
}

bool Checkbox::getState() const{
    return isOn;
}

