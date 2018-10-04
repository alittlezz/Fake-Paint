#include <Utilities.h>

#include <SFML/Graphics.hpp>

#include <algorithm>

namespace Utilities{

std::string toString(int x){
    if(x == 0){
        return "0";
    }
    std::string ret = "";
    while(x){
        ret += (x%10) + '0';
        x /= 10;
    }
    std::reverse(ret.begin(), ret.end());
    return ret;
}

void sleepFor(const double &x){
    sf::Clock clock;
    while(clock.getElapsedTime().asSeconds() < x);
}

}
