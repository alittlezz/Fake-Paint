#ifndef PREVIEWSCREEN_H
#define PREVIEWSCREEN_H

#include <SFML/Graphics.hpp>

class PreviewScreen{
    public:
        PreviewScreen(double x, double y, double width, double height, const sf::Color &color);

        void draw(sf::RenderWindow &window) const;

        void changeColor(const sf::Color &newColor);
    private:
        sf::RectangleShape rect;
};

#endif // PREVIEWSCREEN_H
