#include "FakePaint.h"
#include <Utilities.h>
#include <map>
#include <vector>
#include <iostream>
#include <string>

FakePaint::FakePaint(const int &canvasWidth, const int &canvasHeight, const int &canvasWidthPixels, const int &canvasHeightPixels, const int &barSize){
    brush = new Brush(sf::Color::Black, Types::drawPixel, 3);
    canvas = new Canvas(canvasWidth, canvasHeight, canvasWidthPixels, canvasHeightPixels);
    canvas->setBrush(brush);
    sidebar = new Sidebar(canvasWidth, 0, barSize, canvasHeight);
    lowerbar = new Lowerbar(0, canvasHeight, canvasWidth + barSize, barSize);
    lowerbar->setBrush(brush);
    colorPalette = new ColorPalette(canvasWidth / 1.2, canvasHeight / 1.2);

    totalWidth = canvasWidth + barSize;
    totalHeight = canvasHeight + barSize;
}

FakePaint::~FakePaint(){
    delete canvas;
    delete sidebar;
    delete lowerbar;
    delete brush;
    delete colorPalette;
}

void FakePaint::drawElements(sf::RenderWindow &window) const{
    window.clear(sf::Color::White);
    canvas->draw(window);
    canvas->drawCurrent(window);
    sidebar->draw(window);
    lowerbar->draw(window);
    window.display();
}

void FakePaint::run(){
    sf::RenderWindow window(sf::VideoMode(totalWidth, totalHeight), "FakePaint", sf::Style::Titlebar | sf::Style::Close);
    drawElements(window);
    while(window.isOpen()){
        if(handleEvents(window)){
            drawElements(window);
        }
    }
}

bool FakePaint::handleEvents(sf::RenderWindow &window){
    bool anyEvent = false;
    sf::Event event;
    while(window.pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed :
                window.close();
                anyEvent = true;
                break;

            case sf::Event::KeyPressed :
                if(event.key.code == sf::Keyboard::Escape){
                    window.close();
                    anyEvent = true;
                }else if(event.key.code == sf::Keyboard::Z && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
                    canvas->deleteLastMove();
                    anyEvent = true;
                }
                break;
            case sf::Event::MouseButtonPressed :
                if(event.mouseButton.button == sf::Mouse::Left){
                    Geom::Point mouse(sf::Mouse::getPosition(window));
                    if(sidebar->isInbounds(mouse) == true){
                        Types action = sidebar->handleEvents(mouse);
                        switch(action){
                            case Types::eraser :
                                brush->setType(Types::drawPixel);
                                brush->setColor(sf::Color::White);
                                anyEvent = true;
                                break;
                            case Types::drawPixel :
                                brush->setType(Types::drawPixel);
                                anyEvent = true;
                                break;
                            case Types::drawCircle :
                                brush->setType(Types::drawCircle);
                                anyEvent = true;
                                break;
                            case Types::drawRectangle :
                                brush->setType(Types::drawRectangle);
                                anyEvent = true;
                                break;
                            case Types::pickColor :
                                brush->setColor(colorPalette->getColor(brush->getColor()));
                                Utilities::sleepFor(0.1);
                                anyEvent = true;
                                break;
                            case Types::switchFill :
                                canvas->switchFill();
                                anyEvent = true;
                                break;
                        }
                    }else if(lowerbar->isInbounds(mouse) == true){
                        Types action = lowerbar->getAction(mouse);
                        switch(action){
                            case Types::clearScreen :
                                canvas->clearScreen();
                                anyEvent = true;
                                break;
                            case Types::copyColor :
                                brush->setType(Types::copyColor);
                                anyEvent = true;
                                break;
                            case Types::activatedSlider :
                                lowerbar->handleEvents(mouse);
                                lowerbar->turnOn();
                                anyEvent = true;
                                break;
                        }
                    }else if(canvas->isInbounds(mouse) == true){
                        switch(brush->getType()){
                            case Types::drawPixel :
                                canvas->addPixel(mouse, brush->getColor());
                                canvas->turnBrushOn();
                                anyEvent = true;
                                break;
                            case Types::drawCircle :
                                canvas->addCorner(mouse);
                                canvas->addCorner(mouse);
                                canvas->turnBrushOn();
                                anyEvent = true;
                                break;
                            case Types::drawRectangle :
                                canvas->addCorner(mouse);
                                canvas->addCorner(mouse);
                                canvas->turnBrushOn();
                                anyEvent = true;
                                break;
                            case Types::copyColor :
                                brush->setColor(canvas->getColor(mouse));
                                anyEvent = true;
                                break;
                        }
                    }
                }
                break;
            case sf::Event::MouseButtonReleased :
                if(event.mouseButton.button == sf::Mouse::Left){
                    if(canvas->getBrushState() == true){
                        switch(brush->getType()){
                            case Types::drawPixel :
                                canvas->finishCurrentMove();
                                canvas->turnBrushOff();
                                anyEvent = true;
                                break;
                            case Types::drawCircle :
                                canvas->finishCurrentCircle();
                                canvas->turnBrushOff();
                                anyEvent = true;
                                break;
                            case Types::drawRectangle :
                                canvas->finishCurrentRectangle();
                                canvas->turnBrushOff();
                                anyEvent = true;
                                break;
                        }
                    }else if(lowerbar->getState() == true){
                        lowerbar->turnOff();
                        anyEvent = true;
                        break;
                    }
                }
                break;
        }
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) == true){
        Geom::Point mouse(sf::Mouse::getPosition(window));
        if(canvas->getBrushState() == true){
            switch(brush->getType()){
                case Types::drawPixel :
                    canvas->addPixels(mouse, brush->getColor());
                    anyEvent = true;
                    break;
                case Types::drawCircle :
                    canvas->eraseCurrentMove();
                    canvas->addCorner(mouse);
                    anyEvent = true;
                    break;
                case Types::drawRectangle :
                    canvas->eraseCurrentMove();
                    canvas->addCorner(mouse);
                    anyEvent = true;
                    break;
            }
        }else if(lowerbar->getState() == true){
            lowerbar->handleEvents(mouse);
            anyEvent = true;
        }
    }
    return anyEvent;
}
