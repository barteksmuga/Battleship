//
//  Ship.hpp
//  battleship
//
//  Created by Bartłomiej Smuga on 15/12/2017.
//  Copyright © 2017 Bartłomiej Smuga. All rights reserved.
//

#ifndef SHIP_HPP
#define SHIP_HPP

#include "Point.hpp"
#include <iostream>

#define BOARD_SIZE 10

enum Orientation {left = 1,up = 2,right = 3,down = 4};
Orientation setOrientation(){
    Orientation orientDecision;
    int decision;
    std::cin >> decision;
    orientDecision = static_cast<Orientation>(decision);
    return orientDecision;
}
class Ship;
std::ostream &operator<<(std::ostream&,Ship&);

class Ship{
public:
    Ship(Point&,int);
    Ship(const Ship&);
    ~Ship();
    static int getCounter();
    friend std::ostream &operator<<(std::ostream&,Ship&);
    void setShipLength(int);
    void setShipOrientation();
    void displayShip();
    Orientation getShipOrientation();
    Point getShipStart();
    int getLength();
private:
    Point start, end;
    int shipLength;
    static int counter;
    Orientation orient;
};

int Ship::counter = 0;

Ship::Ship(Point &point, int L): start(point), shipLength(L){
    ++counter;
    setShipOrientation();
    start--;
}
Ship::Ship(const Ship &cpShip){
    start = cpShip.start;
    shipLength = cpShip.shipLength;
    orient = cpShip.orient;
}
Ship::~Ship(){counter--;}

int Ship::getCounter(){return counter;}

void Ship::setShipLength(int length){shipLength = length;}

void Ship::setShipOrientation(){
    std::cout << "Whitch way you wanna set Ship:\n1.Left\n2.Up\n3.Right\n4.Down\n";
    orient = setOrientation();
    switch(orient){
        case left:
            if(start.x - shipLength >= 0){
                end.x = (start.x - shipLength) + 1;
                end.y = start.y;
                break;
            } else {
                std::cout << "Out of board!\nPlease, choose another way\n";
                setShipOrientation();
                break;
            }
        case up:
            if(start.y - shipLength >= 0){
                end.x = start.x;
                end.y = (start.y - shipLength) + 1;
                break;
            } else {
                std::cout << "Out of board!\nPlease, choose another way\n";
                setShipOrientation();
                break;
            }
        case right:
            if(start.y + shipLength <= BOARD_SIZE){
                end.y = (start.y + shipLength) - 1;
                end.x = start.x;
                break;
            } else {
                std::cout << "Out of board!\nPlease, choose another way\n";
                setShipOrientation();
                break;
            }
        case down:
            if(start.x + shipLength <= BOARD_SIZE){
                end.y = start.y;
                end.x = (start.x + shipLength) - 1;
                break;
            } else {
                std::cout << "Out of board!\nPlease, choose another way\n";
                setShipOrientation();
                break;
            }
        default:
            std::cout << "Please, insert number from 1 to 4, to choose direction\n";
            setShipOrientation();
            break;
        }
}
Orientation Ship::getShipOrientation(){return orient;}
void Ship::displayShip(){
    std::cout << "Ship " << getCounter() << ":\n"
    << "Start(" << start.x << "," << start.y << "), "
    << "End(" << end.x << "," << end.y << "), "
    << "Length = " << shipLength << std::endl;
}
Point Ship::getShipStart(){
    return start;
}
int Ship::getLength(){
    return shipLength;
}

//****************************************************************

std::ostream &operator <<(std::ostream &output, Ship &ship){
    output << "Ship " << ship.getCounter() << ":\n"
    << "Start(" << ship.start.x << "," << ship.start.y << "), "
    << "End(" << ship.end.x << "," << ship.end.y << "), "
    << "Length = " << ship.shipLength << std::endl;
    return output;
}

#endif /* SHIP_HPP */
