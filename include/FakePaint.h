#ifndef FAKEPAINT_H
#define FAKEPAINT_H

#include <SFML/Graphics.hpp>

#include <Brush.h>
#include <Canvas.h>
#include <Sidebar.h>
#include <Lowerbar.h>
#include <ColorPalette.h>

class FakePaint{
    public:
        FakePaint(const int &canvasWidth, const int &canvasHeight, const int &canvasWidthPixels, const int &canvasHeightPixels, const int &barSize);
        ~FakePaint();

        void run();
    private:
        void drawElements(sf::RenderWindow &window) const;
        bool handleEvents(sf::RenderWindow &window);

        int totalWidth, totalHeight;

        Brush        *brush;
        Canvas       *canvas;
        Sidebar      *sidebar;
        Lowerbar     *lowerbar;
        ColorPalette *colorPalette;
};

#endif // FAKEPAINT_H
