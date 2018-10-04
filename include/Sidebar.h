#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <Button.h>
#include <Geometry.h>

#include <vector>

class Sidebar{
    public:
        Sidebar(const int &_x, const int &_y, const int &_width, const int &_height);

        void draw     (sf::RenderWindow &window) const;
        void addButton(Button *button);

        int getWidth () const;
        int getHeight() const;

        Types handleEvents(const Geom::Point &mouse);

        bool isInbounds(const Geom::Point &point) const;
    private:
        int x, y;
        int width, height;

        sf::RectangleShape box;

        std::vector <Button*> buttons;
};

#endif // SIDEBAR_H
