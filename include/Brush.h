#ifndef BRUSH_H
#define BRUSH_H

#include <SFML/Graphics.hpp>

#include <Button.h>

class Brush{
    public:
        Brush(const sf::Color &_color, const Types &_type, const int &_size);

        int       getSize () const;
        Types     getType () const;
        sf::Color getColor() const;

        void setSize (const int &_size);
        void setType (const Types &_type);
        void setColor(const sf::Color &_color);
    private:
        int       size;
        int       opacity;
        Types     type;
        sf::Color color;
};

#endif // BRUSH_H
