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


#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"

#include <iostream>
#include "Point.hpp"
#include "Ship.hpp"

const std::string EMPTY_FIELD = "   ";
const std::string SHOT_FIELD = " X ";
const std::string MISSED_FIELD = " 0 ";
const std::string OWN_SHIP = " Z ";

class Field{
public:
    Field();
    bool isShip();
    bool isShot();
    void setShip(Ship*&);
    void setShot();
    void setValue();
    Ship *getShip();
    std::string getSignToPrint(bool);
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

bool Field::isShip() {
    return sship;
}

bool Field::isShot() {
    return shot;
}

void Field::setShip(Ship *&newShip) {
    ship = newShip;
    sship = true;
}

void Field::setShot() {
    shot = true;
}

void Field::setValue() {
    sship = false;
    shot = false;
}

Ship* Field::getShip() {
    return ship;
}

std::string Field::getSignToPrint(bool isOwn) {
    std::string signToDraw;
    std::string colorCode;
    
    if (isOwn) {
        if (isShip()) {
            if (isShot()) {
                signToDraw = SHOT_FIELD;
                colorCode = RED;
            } else {
                signToDraw = OWN_SHIP;
                colorCode = BLUE;
            }
        } else {
            if (isShot()) {
                signToDraw = MISSED_FIELD;
            } else {
                signToDraw = EMPTY_FIELD;
            }
        }
    } else {
        if (isShot()) {
            if (isShip()) {
                signToDraw = SHOT_FIELD;
                colorCode = GREEN;
            } else {
                signToDraw = MISSED_FIELD;
            }
        } else {
            signToDraw = EMPTY_FIELD;
        }
    }

    return colorCode + signToDraw + RESET;
}
#endif /* Field_hpp */
