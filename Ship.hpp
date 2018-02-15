//
//  Ship.hpp
//  battleship
//
//  Created by Bartłomiej Smuga on 15/12/2017.
//  Copyright © 2017 Bartłomiej Smuga
//  Released under the MIT license
//

#ifndef Ship_hpp
#define Ship_hpp

#include <iostream>
#include "Point.hpp"
#include "Direction.hpp"
  
class Ship{
public:
    Ship(int);
    ~Ship();
    void setStart(Point&);
    void setLength(int);
    void setDirection(Direction&);
    Point getStart();
    int getLength();
    Direction getDirection();
    static int getCounter() { return counter;}
private:
    Point start;
    int length;
    Direction direction;
    static int counter;
};
int Ship::counter = 0;
Ship::Ship(int L){
    ++counter;
    setLength(L);
    if(L == 1) {
        direction = left;
    }
}
Ship::~Ship(){
    counter--;
}
void Ship::setStart(Point &point){
    start = point;
}
void Ship::setLength(int L){
    length = L;
}
void Ship::setDirection(Direction &direct){
    direction = direct;
}
Point Ship::getStart(){return start;}
int Ship::getLength(){return length;}
Direction Ship::getDirection(){return direction;}

#endif /* Ship_hpp */
