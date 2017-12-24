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

enum Orientation {left = 1,up = 2,right = 3,down = 4, quit=5};
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
    Ship(int);
    Ship(const Ship&);
    ~Ship();
    static int getCounter();
    friend std::ostream &operator<<(std::ostream&,Ship&);
    void setShipLength(int);
    void setShipOrientation();
    void setShipStart();
    void displayShip();
    Orientation getShipOrientation();
    Point getShipStart();
    Point getShipEnd();
    int getLength();
private:
    Point start, end;
    int shipLength;
    static int counter;
    Orientation orientation;
};

int Ship::counter = 0;

Ship::Ship(int L){
    ++counter;
    setShipStart();
    setShipLength(L);
}
Ship::Ship(const Ship &cpShip){
    start = cpShip.start;
    shipLength = cpShip.shipLength;
    orientation = cpShip.orientation;
}
Ship::~Ship(){counter--;}
void Ship::setShipLength(int length){shipLength = length;}
void Ship::setShipOrientation(){
    std::cout << "Which way you wanna set Ship:\n1.Left\n2.Up\n3.Right\n4.Down\n5.Exit\n";
    orientation = setOrientation();
    switch(orientation){
        case left:
            if(start.y - shipLength >= 0){
                end.x = start.x;
                end.y = start.y - (shipLength-1);
                break;
            } else {
                std::cout << "Out of board!\nPlease, choose another way\n";
                setShipOrientation();
                break;
            }
        case up:
            if(start.x - (shipLength-1) >= 0){
                end.y = start.y;
                end.x = start.x - (shipLength-1);
                break;
            } else {
                std::cout << "Out of board!\nPlease, choose another way\n";
                setShipOrientation();
                break;
            }
        case right:
            if(start.y + shipLength <= BOARD_SIZE+1){
                end.y = start.y + (shipLength-1);
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
                end.x = start.x + (shipLength-1);
                break;
            } else {
                std::cout << "Out of board!\nPlease, choose another way\n";
                setShipOrientation();
                break;
            }
        case quit:
            return;
            break;
        default:
            std::cout << "Please, insert number from 1 to 4, to choose direction, or 5 to exit\n";
            setShipOrientation();
            break;
        }
}
void Ship::setShipStart(){
    std::cout << "Insert start coordinates: ";
    std::cin >> start;
    if(start.x >= BOARD_SIZE || start.y >= BOARD_SIZE){
        std::cout << "Board size is " << BOARD_SIZE << ". Insert a number between 0 - 9\n";
        setShipStart();
    }
    if(start.x < 0 || start.y < 0){
        std::cout << "Coordinates must be bigger or equal 0. Try again\n";
        setShipStart();
    }
//    if(start.x > 0 && start.y > 0)
//        start--;
//    if(start.x == 0 && start.y > 0)
//        start.y--;
//    if(start.x > 0 && start.y == 0)
//        start.x--;
}

void Ship::displayShip(){
    std::cout << "Ship " << getCounter() << ":\n"
    << "Start(" << start.x << "," << start.y << "), "
    << "End(" << end.x << "," << end.y << "), "
    << "Length = " << shipLength << std::endl;
}
Orientation Ship::getShipOrientation(){return orientation;}
Point Ship::getShipStart(){return start;}
Point Ship::getShipEnd(){return end;}
int Ship::getLength(){return shipLength;}
int Ship::getCounter(){return counter;}
//****************************************************************
std::ostream &operator <<(std::ostream &output, Ship &ship){
    output << "Ship " << ship.getCounter() << ":\n"
    << "Start(" << ship.start.x << "," << ship.start.y << "), "
    << "End(" << ship.end.x << "," << ship.end.y << "), "
    << "Length = " << ship.shipLength << std::endl;
    return output;
}

#endif /* SHIP_HPP */
