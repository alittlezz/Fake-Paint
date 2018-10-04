#include "ColorPalette.h"
#include <Resources.h>

ColorPalette::ColorPalette(int _width, int _height){
    width = _width;
    height = _height;
    primaryColorPalette = new PrimaryColorPalette(borderSize * width / 100, (borderSize + 65 + borderSize) * height / 100, 94.6 * width / 100, 4.2 * height / 100);
    secondaryColorPalette = new SecondaryColorPalette((borderSize + 29.8 + borderSize) * width / 100 + 15, borderSize * height / 100, 62.1 * width / 100 - 15, 60 * height / 100);
    previewScreen = new PreviewScreen(borderSize * width / 100, borderSize * height / 100, 29.8 * width / 100, 60 * height / 100, secondaryColorPalette->slider->getColor());
    accept = new Button((borderSize + 10) * width / 100, (borderSize + 70 + borderSize + borderSize) * height / 100, Resources::resourceManager.getTexture("on.png"), Types::DEFAULT_ACTION, sf::Vector2f(96.0 / 128.0, 96.0 / 128.0));
    cancel = new Button((borderSize + 39.8 + 25) * width / 100, (borderSize + 70 + borderSize + borderSize) * height / 100, Resources::resourceManager.getTexture("off.png"), Types::DEFAULT_ACTION, sf::Vector2f(96.0 / 128.0, 96.0 / 128.0));
}

ColorPalette::~ColorPalette(){
    delete primaryColorPalette;
    delete secondaryColorPalette;
    delete previewScreen;
    delete accept;
    delete cancel;
}


sf::Color ColorPalette::getColor(const sf::Color &currentColor){
    sf::RenderWindow window(sf::VideoMode(width, height), "Color palette", sf::Style::Titlebar | sf::Style::Close);
    sf::Color newColor = currentColor;
    while(window.isOpen()){
        newColor = handleEvents(window, currentColor);
        window.clear();
        primaryColorPalette->draw(window);
        secondaryColorPalette->draw(window);
        previewScreen->draw(window);
        accept->draw(window);
        cancel->draw(window);
        window.display();
    }
    return newColor;
}

sf::Color ColorPalette::handleEvents(sf::RenderWindow &window, const sf::Color &currentColor){
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window.close();
        }else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
            window.close();
        }else if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){
            primaryColorPalette->slider->turnOff();
            secondaryColorPalette->slider->turnOff();
        }else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
            Geom::Point mouse(sf::Mouse::getPosition(window));
            if(primaryColorPalette->slider->isInbounds(mouse) == true){
                primaryColorPalette->slider->turnOn();
                primaryColorPalette->slider->update(mouse);
                primaryColorPalette->changeColor();
                secondaryColorPalette->changeColor(primaryColorPalette->slider->getColor());
                previewScreen->changeColor(secondaryColorPalette->slider->getColor());
            }else if(secondaryColorPalette->slider->isInbounds(mouse) == true){
                secondaryColorPalette->slider->turnOn();
                secondaryColorPalette->slider->update(mouse);
                secondaryColorPalette->changeColor();
                previewScreen->changeColor(secondaryColorPalette->slider->getColor());
            }else if(accept->isInbounds(mouse) == true){
                window.close();
                return secondaryColorPalette->slider->getColor();
            }else if(cancel->isInbounds(mouse) == true){
                window.close();
            }
        }
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        Geom::Point mouse(sf::Mouse::getPosition(window));
        if(primaryColorPalette->slider->getState() == true){
            primaryColorPalette->slider->update(mouse);
            primaryColorPalette->changeColor();
            secondaryColorPalette->changeColor(primaryColorPalette->slider->getColor());
            previewScreen->changeColor(secondaryColorPalette->slider->getColor());
        }else if(secondaryColorPalette->slider->getState() == true){
            secondaryColorPalette->slider->update(mouse);
            secondaryColorPalette->changeColor();
            previewScreen->changeColor(secondaryColorPalette->slider->getColor());
        }
    }
    return currentColor;
}
