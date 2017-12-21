//
//  Board.hpp
//  battleship
//
//  Created by Bartłomiej Smuga on 18/12/2017.
//  Copyright © 2017 Bartłomiej Smuga. All rights reserved.
//

#ifndef BOARD_HPP
#define BOARD_HPP

#include "Ship.hpp"
#include "Field.hpp"
#include "Point.hpp"
#include <iostream>
#include <iomanip>

#define BOARD_SIZE 10

class Board{
public:
    Field &operator [](Point&);
    void displayBoard();
    void setShipOnBoard(Ship*&);
private:
    Field board[BOARD_SIZE][BOARD_SIZE];
};
Field & Board::operator [](Point &point){
    return board[point.x][point.y];
}
void Board::displayBoard(){
    const int cwidth = 3;
    int y=1;
    for(int x=0; x<11; x++){
        std::cout << std::setw(cwidth) << x << "|";
    }
    
    std::cout << std::endl;
    std::cout << " ";
    for(int k=0; k<=BOARD_SIZE; k++)
        std::cout << std::setw(cwidth) << "----";
    
    std::cout << std::endl;
    for(int i=0; i<BOARD_SIZE; i++){
        std::cout << std::setw(cwidth) << y << "|";
        for(int j=0; j<BOARD_SIZE; j++){
            if(board[i][j].isShip()){
                std::cout << std::setw(cwidth) << " 0 |";
            } else {
                std::cout << std::setw(cwidth) << " - |";
            }
        }
        y++;
        std::cout << std::endl;
        std::cout << " ";
        for(int k=0; k<=BOARD_SIZE; k++)
            std::cout << std::setw(cwidth) << "----";
        std::cout << std::endl;
    }
}
void Board::setShipOnBoard(Ship *&ship){
    Point temporary = ship->getShipStart();
    
    switch(ship->getShipOrientation()){
        case left:
            for(int i=(temporary.y); i>(temporary.y - ship->getLength()); i--){
                board[temporary.x][i].setShip(ship);
            }
            break;
        case up:
            for(int i=temporary.x; i>(temporary.x - ship->getLength()); i--){
                board[i][temporary.y].setShip(ship);
            }
            break;
        case right:
            for(int i=temporary.y; i<(temporary.y + ship->getLength()); i++){
                board[temporary.x][i].setShip(ship);
            }
            break;
        case down:
            for(int i=temporary.x; i<(temporary.x + ship->getLength()); i++){
                board[i][temporary.y].setShip(ship);
            }
            break;
    }
}

#endif /* BOARD_HPP */


