#include "Canvas.h"
#include <Utilities.h>

#include <math.h>

Canvas::Canvas(const int &_width, const int &_height, const int &_widthPixels, const int &_heightPixels){
    width = _width;
    height = _height;
    widthPixels = _widthPixels;
    heightPixels = _heightPixels;
    delimiterWidth = (double)width / widthPixels;
    delimiterHeight = (double)height / heightPixels;
}

Canvas::~Canvas(){
    delete brush;
}

void Canvas::draw(sf::RenderWindow &window) const{
    int pixelIndex = 0;
    int circleIndex = 0;
    int rectangleIndex = 0;
    for(auto &it : lastShape){
        if(it == 0){
            sf::CircleShape pixel;
            Brush currentBrush = moves[pixelIndex].second;
            pixel.setRadius(currentBrush .getSize());
            pixel.setFillColor(currentBrush .getColor());
            for(auto &point : moves[pixelIndex].first){
                pixel.setPosition(sf::Vector2f(point.getX(), point.getY()));
                window.draw(pixel);
            }
            pixelIndex++;
        }else if(it == 1){
            window.draw(circles[circleIndex]);
            circleIndex++;
        }else if(it == 2){
            window.draw(rectangles[rectangleIndex]);
            rectangleIndex++;
        }
    }
}

sf::CircleShape Canvas::getCircle(const Geom::Point &A, const Geom::Point &B) const{
    sf::CircleShape circle;
    double l = std::min(std::fabs(A.getX() - B.getX()), std::fabs(A.getY() - B.getY()));
    double x = A.getX() - (A.getX() > B.getX() ? l : 0);
    double y = A.getY() - (A.getY() > B.getY() ? l : 0);
    circle.setPosition(sf::Vector2f(x, y));
    circle.setRadius(l / 2.0);
    if(isFillOn){
        circle.setFillColor(brush->getColor());
    }else{
        sf::Color invisible = brush->getColor();
        invisible.a = 0;
        circle.setFillColor(invisible);
        circle.setOutlineColor(brush->getColor());
        circle.setOutlineThickness(brush->getSize());
    }
    return circle;
}

sf::RectangleShape Canvas::getRectangle(const Geom::Point &A, const Geom::Point &B) const{
    sf::RectangleShape rectangle;
    rectangle.setPosition(sf::Vector2f(std::min(A.getX(), B.getX()), std::min(A.getY(), B.getY())));
    double dX = std::fabs(A.getX() - B.getX());
    double dY = std::fabs(A.getY() - B.getY());
    rectangle.setSize(sf::Vector2f(dX, dY));
    if(isFillOn){
        rectangle.setFillColor(brush->getColor());
    }else{
        sf::Color invisible = brush->getColor();
        invisible.a = 0;
        rectangle.setFillColor(invisible);
        rectangle.setOutlineColor(brush->getColor());
        rectangle.setOutlineThickness(brush->getSize());
    }
    return rectangle;
}



void Canvas::drawCurrent(sf::RenderWindow &window) const{
    if(currentMove.empty() == true){
        return;
    }
    switch(brush->getType()){
        case Types::drawPixel :{
                sf::CircleShape pixel;
                pixel.setRadius(brush->getSize());
                pixel.setFillColor(brush->getColor());
                for(auto &position : currentMove){
                    pixel.setPosition(sf::Vector2f(position.getX(), position.getY()));
                    window.draw(pixel);
                }
            }
            break;
        case Types::drawCircle :{
                sf::CircleShape circle = getCircle(currentMove.front(), currentMove.back());
                window.draw(circle);
            }
            break;
        case Types::drawRectangle :{
                sf::RectangleShape rectangle = getRectangle(currentMove.front(), currentMove.back());
                window.draw(rectangle);
            }
            break;
    }
}

void Canvas::clearScreen(){
    moves.clear();
    circles.clear();
    rectangles.clear();
    lastShape.clear();
}

void Canvas::addPixel(const Geom::Point &newPoint, const sf::Color &newColor){
    currentMove.push_back(newPoint - brush->getSize());
}

void Canvas::addCorner(const Geom::Point &newPoint){
    currentMove.push_back(newPoint);
}

void Canvas::addPixels(const Geom::Point &newPoint, const sf::Color &newColor){
    if(currentMove.empty() == true){
        addPixel(newPoint, newColor);
        return;
    }
    Geom::Point lastPoint = Geom::Point(*(currentMove.rbegin())) + brush->getSize();
    if(lastPoint == newPoint){
        return;
    }
    Geom::Line line(newPoint, lastPoint);
    Geom::Point moveRatio;
    if(line.getB() == 0){
        moveRatio = Geom::Point(0, brush->getSize());
        if(lastPoint.getY() > newPoint.getY()){
            moveRatio = moveRatio * -1;
        }
    }else{
        double percentage = (Utilities::PI / 2 -
                             fabs(atan(-line.getA() /
                                        line.getB()))) /
                            (Utilities::PI / 2);
        moveRatio = Geom::Point(brush->getSize() * percentage,
        -line.getA() * brush->getSize() * percentage/ line.getB());
        if(lastPoint.getX() > newPoint.getX()){
            moveRatio = moveRatio * -1;
        }
    }

    double distance = Geom::distance(newPoint, lastPoint);
    for(Geom::Point currentPoint = lastPoint + moveRatio;
        Geom::distance(currentPoint, lastPoint) < distance;
        currentPoint = currentPoint + moveRatio){

        addPixel(currentPoint, newColor);
    }
    addPixel(newPoint, newColor);
}

void Canvas::deleteLastMove(){
    if(lastShape.empty() == true){
        return;
    }
    if(lastShape.back() == 0){
        moves.pop_back();
    }else if(lastShape.back() == 1){
        circles.pop_back();
    }else if(lastShape.back() == 2){
        rectangles.pop_back();
    }
    lastShape.pop_back();
}

void Canvas::eraseCurrentMove(){
    if(currentMove.empty() == true){
        return;
    }
    currentMove.pop_back();
}

void Canvas::finishCurrentMove(){
    if(currentMove.empty() == true){
        return;
    }
    std::vector <Geom::Point> auxiliary;
    for(auto &point : currentMove){
        if(isInbounds(point) || isInbounds(point + 2 * brush->getSize())){
            auxiliary.emplace_back(point);
        }
    }
    moves.push_back({auxiliary, *brush});
    lastShape.emplace_back(0);
    currentMove.clear();
}

void Canvas::finishCurrentCircle(){
    if(currentMove.empty() == true){
        return;
    }
    sf::CircleShape circle = getCircle(currentMove.front(), currentMove.back());
    circles.push_back(circle);
    lastShape.emplace_back(1);
    currentMove.clear();
}

void Canvas::finishCurrentRectangle(){
    if(currentMove.empty() == true){
        return;
    }
    sf::RectangleShape rectangle = getRectangle(currentMove.front(), currentMove.back());
    rectangles.push_back(rectangle);
    lastShape.emplace_back(2);
    currentMove.clear();
}

int Canvas::getWidth() const{
    return width;
}

int Canvas::getHeight() const{
    return height;
}

bool Canvas::getBrushState() const{
    return isBrushOn;
}

sf::Color Canvas::getColor(const Geom::Point &mouse) const{
    sf::Color lastColor = sf::Color::White;
    int pixelIndex = 0;
    int circleIndex = 0;
    int rectangleIndex = 0;
    for(auto &it : lastShape){
        if(it == 0){
            sf::CircleShape pixel;
            Brush currentBrush = moves[pixelIndex].second;
            pixel.setRadius(currentBrush .getSize());
            pixel.setFillColor(currentBrush .getColor());
            for(auto &point : moves[pixelIndex].first){
                pixel.setPosition(sf::Vector2f(point.getX(), point.getY()));
                if(Geom::inCircle(mouse, pixel) == true){
                    lastColor = pixel.getFillColor();
                }
            }
            pixelIndex++;
        }else if(it == 1){
            if(circles[circleIndex].getFillColor().a == 0){
                if(Geom::inCircleOutline(mouse, circles[circleIndex]) == true){
                    lastColor = circles[circleIndex].getOutlineColor();
                }
            }else{
                if(Geom::inCircle(mouse, circles[circleIndex]) == true){
                    lastColor = circles[circleIndex].getFillColor();
                }
            }
            circleIndex++;
        }else if(it == 2){
            if(rectangles[rectangleIndex].getFillColor().a == 0){
                if(Geom::inRectangleOutline(mouse, rectangles[rectangleIndex]) == true){
                    lastColor = rectangles[rectangleIndex].getOutlineColor();
                }
            }else{
                if(Geom::inRectangle(mouse, rectangles[rectangleIndex]) == true){
                    lastColor = rectangles[rectangleIndex].getFillColor();
                }
            }
            rectangleIndex++;
        }
    }
    return lastColor;
}

void Canvas::turnBrushOn(){
    isBrushOn = true;
}

void Canvas::turnBrushOff(){
    isBrushOn = false;
}

void Canvas::setBrush(Brush *_brush){
    brush = _brush;
}

void Canvas::switchFill(){
    isFillOn = !isFillOn;
}

bool Canvas::isInbounds(const Geom::Point &point) const{
    return 0 <= point.getX() && point.getX() < width && 0 <= point.getY() && point.getY() < height;
}

bool Canvas::isInbounds(const int &x, const int &y) const{
    return 0 <= x && x < widthPixels && 0 <= y && y < heightPixels;
}

bool Canvas::isInbounds(const std::pair <double, double> &pixel) const{
    return 0 <= pixel.first && pixel.first < widthPixels && 0 <= pixel.second && pixel.second < heightPixels;
}
