
//  main.cpp
//  battleship
//
//  Created by Bartłomiej Smuga on 15/12/2017.
//  Copyright © 2017 Bartłomiej Smuga. All rights reserved.
//
#include "Board.hpp"
#include "Field.hpp"
#include "Ship.hpp"
#include "Point.hpp"
#include <iostream>

#define EXIT_SUCCES 0

int main(){
//    {
//    Point point(3, 5);
//    Ship *ship = new Ship(point,4);
//    Field field(point);
//    field.setShip(ship);
//    std::cout << field;
//    }
//    std::cout << Ship::getCounter() << std::endl;
    Point point(8,5);
    Board board;
    Ship *ship = new Ship(point,4);
    board.setShipOnBoard(ship);
    board.displayBoard();
    return EXIT_SUCCESS;
}
