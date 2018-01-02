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

#define AREA_SIZE 12
#define BOARD_SIZE 10

class Board{
public:
    Board();
    Field &operator [](Point&);
    void displayShipsOnBoard();
    void displayShotsOnBoard();
    void setShipOnBoard(Ship*&);
    void takeAShotOnBoard(Point&);
    bool checkAroundShip(Ship*&);
    bool isShipOnField(Point&);
    bool correctShot(Point&);
private:
    Field board[AREA_SIZE][AREA_SIZE];
};
Board::Board(){
    for(int i=0; i<AREA_SIZE; i++)
        for(int j=0; j<AREA_SIZE; j++)
            board[i][j].setBoolValueFalse();
}
Field & Board::operator [](Point &point){
    return board[point.x][point.y];
}
void Board::displayShipsOnBoard(){
    const int CWIDTH = 3;
    int y=0;
    std::cout << std::setw(CWIDTH) << "   |";
    for(int x=0; x<10; x++)
        std::cout << std::setw(CWIDTH) << x << "|";
    
    
    std::cout << std::endl;
    std::cout << " ";
    for(int k=0; k<=BOARD_SIZE; k++)
        std::cout << std::setw(CWIDTH) << "----";
    
    std::cout << std::endl;
    for(int i=0; i<BOARD_SIZE; i++){
        std::cout << std::setw(CWIDTH) << y << "|";
        for(int j=0; j<BOARD_SIZE; j++){
            if(board[i][j].isShip()){
                std::cout << std::setw(CWIDTH) << " 0 |";
            } else {
                std::cout << std::setw(CWIDTH) << "   |";
            }
        }
        y++;
        std::cout << std::endl;
        std::cout << " ";
        for(int k=0; k<=BOARD_SIZE; k++)
            std::cout << std::setw(CWIDTH) << "----";
        
        std::cout << std::endl;
    }
}
void Board::displayShotsOnBoard(){
    std::cout << "\n\n\tSHOTS BOARD: \n";
    const int CWIDTH = 3;
    int y=0;
    std::cout << std::setw(CWIDTH) << "   |";
    for(int x=0; x<10; x++){
        std::cout << std::setw(CWIDTH) << x << "|";
    }
    
    std::cout << std::endl;
    std::cout << " ";
    for(int k=0; k<=BOARD_SIZE; k++)
        std::cout << std::setw(CWIDTH) << "----";
    
    std::cout << std::endl;
    for(int i=0; i<BOARD_SIZE; i++){
        std::cout << std::setw(CWIDTH) << y << "|";
        for(int j=0; j<BOARD_SIZE; j++){
            if(board[i][j].isShot()){
                if(board[i][j].isShip())
                    std::cout << std::setw(CWIDTH) << " x |";
                else
                    std::cout << std::setw(CWIDTH) << " o |";
            } else {
                std::cout << std::setw(CWIDTH) << "   |";
            }
        }
        y++;
        std::cout << std::endl;
        std::cout << " ";
        for(int k=0; k<=BOARD_SIZE; k++)
            std::cout << std::setw(CWIDTH) << "----";
        std::cout << std::endl;
    }
}
void Board::setShipOnBoard(Ship *&ship){
    Point temporary = ship->getShipStart();
    ship->setShipOrientation();
    bool state;
    switch(ship->getShipOrientation()){
        case left:
            state = checkAroundShip(ship);
            if(state){
                std::cout << "ship touches another one\n";
                ship->setShipStart();
                setShipOnBoard(ship);
            } else {
                for(int i=(temporary.y); i>(temporary.y - ship->getLength()); i--){
                    board[temporary.x][i].setShip(ship);
                }
            }
            break;
        case up:
            if(checkAroundShip(ship)){
                std::cout << "ship touches another one\n";
                ship->setShipStart();
                setShipOnBoard(ship);
            } else {
                for(int i=temporary.x; i>(temporary.x - ship->getLength()); i--){
                    board[i][temporary.y].setShip(ship);
                }
            }
            break;
        case right:
            if(checkAroundShip(ship)){
                std::cout << "ship touches another one\n";
                ship->setShipStart();
                setShipOnBoard(ship);
            } else {
                for(int i=temporary.y; i<(temporary.y + ship->getLength()); i++){
                    board[temporary.x][i].setShip(ship);
                }
            }
            
            break;
        case down:
            if(checkAroundShip(ship)){
                std::cout << "ship touches another one\n";
                ship->setShipStart();
                setShipOnBoard(ship);
            } else {
                for(int i=temporary.x; i<(temporary.x + ship->getLength()); i++){
                    board[i][temporary.y].setShip(ship);
                }
            }
            break;
    }
}
bool Board::checkAroundShip(Ship *&ship){
    Point start_ = ship->getShipStart();
    Point end_ = ship->getShipEnd();
    int length_ = ship->getLength();
    Orientation orientation_ = ship->getShipOrientation();
    
    if(orientation_ == left){
        for(int i=(start_.y); i>(start_.y - length_); i--){
            if(board[start_.x-1][i].isShip() || board[start_.x+1][i].isShip())
                return true;
        }
        if(board[start_.x][start_.y+1].isShip() || board[start_.x][end_.y-1].isShip())
                return true;
    }
    
    if(orientation_ == right){
        for(int i=(start_.y); i<(start_.y + length_); i++){
            if(board[start_.x - 1][i].isShip() || board[start_.x + 1][i].isShip())
                return true;
        }
        if(board[start_.x][(start_.y-1)].isShip() || board[start_.x][(end_.y+1)].isShip())
                return true;
    }
    
    if(orientation_ == up){
        for(int i=(start_.x); i>(start_.x-length_); i--){
            if(board[i][start_.y-1].isShip() || board[i][start_.y+1].isShip())
                return true;
        }
        if(board[start_.x+1][start_.y].isShip() || board[end_.x-1][start_.y].isShip())
                return true;
    }
    
    if(orientation_ == down){
        for(int i=(start_.x); i<(start_.x + length_); i++){
            if(board[i][start_.y-1].isShip() || board[i][start_.y+1].isShip())
                return true;
        }
        if(board[start_.x-1][start_.y].isShip() || board[end_.x][start_.y].isShip()){
                return true;
        }
    }
    
    return false;
}
void Board::takeAShotOnBoard(Point &point){
    board[point.x][point.y].takeShot();
}
bool Board::isShipOnField(Point &shot){
    if(board[shot.x][shot.y].isShip())
        return true;
    else
        return false;
        
}

#endif /* BOARD_HPP */
