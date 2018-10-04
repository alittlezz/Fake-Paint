#ifndef CHECKBOX_H
#define CHECKBOX_H


#include <SFML/Graphics.hpp>

#include <Button.h>

class Checkbox : public Button{
    public:
        Checkbox(const int &x, const int &y, const Types &_type, const std::string &_text, const double &scale = 1);

        void switchFill();

        void draw(sf::RenderWindow &window) const;

        bool getState() const;
    private:
        sf::Text text;
        bool isOn;
};

#endif // CHECKBOX_H
