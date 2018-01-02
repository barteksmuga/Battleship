//
//  Field.hpp
//  battleship
//
//  Created by Bartłomiej Smuga on 15/12/2017.
//  Copyright © 2017 Bartłomiej Smuga. All rights reserved.
//

#ifndef FIELD_HPP
#define FIELD_HPP

#include "Ship.hpp"
#include "Point.hpp"
#include <iostream>
class Field;
std::ostream &operator<<(std::ostream&,Field&);

class Field{
public:
    Field(Point&);
    Field();
    ~Field();
    friend std::ostream &operator <<(std::ostream&,Field&);
    void setShip(Ship*&);
    void takeShot();
    void setBoolValueFalse();
    static int getCounter(){return counter;}
    int getCoordinates(char);
    bool isShip();
    bool isShot();
    bool correctShot(Point&);
private:
    static int counter;
    Point coordinates;
    Ship *ship;
    bool bship;
    bool shot;
};
int Field::counter = 0;
Field::Field(){
    ++counter;
    ship = nullptr;
    bship = false;
    shot = false;
}
Field::Field(Point &point): coordinates(point){++counter;ship = nullptr;}
Field::~Field(){counter--;}
void Field::setShip(Ship *&myShip){
    ship = myShip;
    bship = true;
}
void Field::takeShot(){shot = true;}
void Field::setBoolValueFalse(){
    bship = false;
    shot = false;
}
int Field::getCoordinates(char sign){
    if(sign == 'x' || sign == 'X')
        return Field::coordinates.x;
    else
        return Field::coordinates.y;
}

bool Field::isShip(){return bship;}
bool Field::isShot(){return shot;}

//*************************************************************************************
std::ostream &operator <<(std::ostream &output, Field &field){
    output << "Field " << field.getCounter() << ":\n"
    << "Coordinates(" << field.coordinates.x << "," << field.coordinates.y << ")\n";
    if(field.ship){
        output << "Ship: ";
        field.ship->displayShip();
    } else {
        output << "No ship on field\n";
    }
    return output;
}


#endif /* FIELD_HPP */

