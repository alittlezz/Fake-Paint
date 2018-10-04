#ifndef LOWERBAR_H
#define LOWERBAR_H

#include <Brush.h>
#include <Button.h>
#include <Slider.h>
#include <Geometry.h>

#include <vector>

class Lowerbar{
    public:
        Lowerbar(const int &_x, const int &_y, const int &_width, const int &_height);
        ~Lowerbar();

        void draw     (sf::RenderWindow &window) const;

        void addButton(Button *button);
        void addSlider(Slider slider);

        int getWidth () const;
        int getHeight() const;
        bool getState() const;

        void turnOn();
        void turnOff();
        void setBrush(Brush *_brush);

        Types getAction(const Geom::Point &mouse);
        void handleEvents(const Geom::Point &mouse);

        bool isInbounds(const Geom::Point &point) const;
    private:
        int  x, y;
        int  width, height;
        bool isActive = false;

        Brush *brush;

        sf::RectangleShape box;

        std::vector <Slider>   sliders;
        std::vector <Button*>  buttons;
        std::vector <sf::Text> texts;
        std::vector <sf::Text> labels;
};

#endif // LOWERBAR_H
