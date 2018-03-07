//
//  Field.hpp
//  battleship
//
//  Created by Bartłomiej Smuga on 15/12/2017.
//  Copyright © 2017 Bartłomiej Smuga
//  Released under the MIT license
//

#ifndef Field_hpp
#define Field_hpp

#include <iostream>
#include "Point.hpp"
#include "Ship.hpp"
 
class Field{
    
public:
    Field();
    bool isShip();
    bool isShot();
    void setShip(Ship*&);
    void setShot();
    void setValue();
    Ship *getShip();
private:
    Ship *ship;
    bool sship;
    bool shot;
};
Field::Field(){
    ship = nullptr;
    sship = false;
    shot = false;
}
bool Field::isShip(){
    return sship;
}
bool Field::isShot(){
    return shot;
}
void Field::setShip(Ship *&newShip){
    ship = newShip;
    sship = true;
}
void Field::setShot(){
    shot = true;
}
void Field::setValue(){
    sship = false;
    shot = false;
}
Ship* Field::getShip(){
    return ship;
}

#endif /* Field_hpp */
