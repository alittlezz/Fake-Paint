#include "Lowerbar.h"

#include <map>
#include <string>
#include <Resources.h>
#include <Checkbox.h>

Lowerbar::Lowerbar(const int &_x, const int &_y, const int &_width, const int &_height){
    x = _x;
    y = _y;
    width = _width;
    height = _height;

    box.setPosition(sf::Vector2f(x, y));
    box.setSize(sf::Vector2f(width, height));
    sf::Color background(212, 212, 212);
    box.setFillColor(background);

    addButton(new Button(x + 0.1 * width / 5, y + height / 10, Resources::resourceManager.getTexture("clearScreen.png"), Types::clearScreen, sf::Vector2f(64.0 / 96.0, 64.0 / 96.0)));
    addButton(new Button(x + 1.1 * width / 5, y + height / 10, Resources::resourceManager.getTexture("copyColor.png"), Types::copyColor, sf::Vector2f(64.0 / 96.0, 64.0 / 96.0)));

    sf::Text text;
    text.setFont(Resources::resourceManager.getFont("arial.ttf"));
    text.setCharacterSize(20);
    text.setColor(sf::Color::Black);

    sf::Color sliderBox = sf::Color::White;
    sf::Color sliderWheel(220,20,60);
    addSlider(Slider(x + 2.1 * width / 5, y + height / 2, width / 5, height / 10, sliderBox, sliderWheel, true, true));
    addSlider(Slider(x + 3.5 * width / 5, y + height / 2, width / 5, height / 10, sliderBox, sliderWheel, true, true));
    if(sliders.empty() == true){
        int lul = 4128;
    }
    sliders.back().update(Geom::Point(9999, y + height / 1.80));

    text.setPosition(sf::Vector2f(x + 2 * width / 5, y + height / 5));
    text.setString("Dimensiune perie");
    labels.push_back(text);

    text.setPosition(sf::Vector2f(x + 3.70 * width / 5, y + height / 5));
    text.setString("Opacitate");
    labels.push_back(text);

}

Lowerbar::~Lowerbar(){
    delete brush;
}

void Lowerbar::draw(sf::RenderWindow &window) const{
    window.draw(box);
    for(auto &button : buttons){
        button->draw(window);
    }
    for(auto &slider : sliders){
        slider.draw(window);
    }
    for(auto &label : labels){
        window.draw(label);
    }
}

void Lowerbar::addButton(Button *button){
    buttons.push_back(button);
}

void Lowerbar::addSlider(Slider slider){
    sliders.push_back(slider);
}

int Lowerbar::getWidth() const{
    return width;
}

int Lowerbar::getHeight() const{
    return height;
}

bool Lowerbar::getState() const{
    return isActive;
}

void Lowerbar::turnOn(){
    isActive = true;
}

void Lowerbar::setBrush(Brush *_brush){
    brush = _brush;
}

void Lowerbar::turnOff(){
    for(auto &slider : sliders){
        slider.turnOff();
    }
    isActive = false;
}

Types Lowerbar::getAction(const Geom::Point &mouse){
    for(auto &button : buttons){
        if(button->isInbounds(mouse) == true){
            if(button->getType() == Types::switchFill){
                static_cast <Checkbox*>(button)->switchFill();
            }
            return button->getType();
        }
    }
    for(auto &slider : sliders){
        if(slider.isInbounds(mouse)){
            slider.turnOn();
            return Types::activatedSlider;
        }
    }
    return Types::DEFAULT_ACTION;
}

void Lowerbar::handleEvents(const Geom::Point &mouse){
    int sliderIndex = 0;
    for(auto &slider : sliders){
        if(slider.getState() == true){
            slider.update(mouse);
            double percentage = slider.getRatio().getX();
            if(sliderIndex == 0){
                brush->setSize(3 + percentage * 20);
            }else{
                sf::Color lastColor = brush->getColor();
                lastColor.a = percentage * 255;
                brush->setColor(lastColor);
            }
            break;
        }
        sliderIndex++;
    }
}

bool Lowerbar::isInbounds(const Geom::Point &point) const{
    return Geom::Rectangle(box).isInbounds(point);
}
