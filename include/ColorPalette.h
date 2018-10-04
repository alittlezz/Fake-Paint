#ifndef COLORPALETTE_H
#define COLORPALETTE_H

#include <SFML/Graphics.hpp>

#include <PrimaryColorPalette.h>
#include <SecondaryColorPalette.h>
#include <PreviewScreen.h>

#include <Button.h>

class ColorPalette{
    public:
        ColorPalette(int _width, int _height);
        ~ColorPalette();

        sf::Color handleEvents(sf::RenderWindow &window, const sf::Color &currentColor);

        sf::Color getColor(const sf::Color &currentColor);
    private:
        int width, height;

        PrimaryColorPalette   *primaryColorPalette;
        SecondaryColorPalette *secondaryColorPalette;
        PreviewScreen         *previewScreen;

        Button *accept;
        Button *cancel;

        const static int borderSize = 2.7;
};

#endif // COLORPALETTE_H
