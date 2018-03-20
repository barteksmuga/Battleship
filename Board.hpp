//
//  Board.hpp
//  battleship
//
//  Created by Bartłomiej Smuga on 18/12/2017.
//  Copyright © 2017 Bartłomiej Smuga
//  Released under the MIT license
//

#ifndef Board_hpp
#define Board_hpp


#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"

#include <iostream>
#include <iomanip>
#include "Point.hpp"
#include "Field.hpp"
#include "Ship.hpp"
#include "Direction.hpp"

#define AREA_SIZE 12
#define BOARD_SIZE 10

const char HORIZONTAL_SEPARATOR = '-';
const char VERTICAL_SEPARATOR = '|';

class Board{
public:
    Board();
    bool checkAroundShip(Ship*&);
    void setShipOnBoard(Ship*&);
    void takeAShotOnBoard(Point&);
    bool isShip(Point&);
    Ship *getShip(Point&);
    void displayShipsOnBoard();
    void displayShotsOnBoard();
    bool isShot(Point&);
    void drawBoard(bool);
    void printHorizontalLine();
    void printHeader();
    bool isCorrect(Point&);
    bool isSunken(Ship*&,Point&);
private:
    Field board[AREA_SIZE][AREA_SIZE];
};

Board::Board() {
    for(int i=0; i<AREA_SIZE; i++)
        for (int j=0; j<AREA_SIZE; j++)
            board[i][j].setValue();
};

bool Board::checkAroundShip(Ship *&ship) {
    Point start_ = ship->getStart();
    Point end_ = start_;
    int length_ = ship->getLength();
    Direction direction_ = ship->getDirection();
    switch(direction_){
        case left:
            end_.y = (start_.y - length_)+1;
            for(int i=(start_.y); i>(start_.y - length_); i--){
                if(board[start_.x-1][i].isShip() || board[start_.x+1][i].isShip())
                    return true;
            }
            if(board[start_.x][start_.y+1].isShip() || board[start_.x][end_.y-1].isShip()){
                    return true;
            } else {
                    return false;
            }
            break;
        case up:
            end_.x = (start_.x - length_)+1;
            for(int i=(start_.x); i>(start_.x-length_); i--){
                if(board[i][start_.y-1].isShip() || board[i][start_.y+1].isShip())
                    return true;
            }
            if(board[start_.x+1][start_.y].isShip() || board[end_.x-1][start_.y].isShip()){
                return true;
            } else {
                    return false;
            }
            break;
        case right:
            end_.y = (start_.y + length_)-1;
            for(int i=(start_.y); i<(start_.y + length_); i++){
                if(board[start_.x - 1][i].isShip() || board[start_.x + 1][i].isShip())
                    return true;
            }
            if(board[start_.x][(start_.y-1)].isShip() || board[start_.x][(end_.y+1)].isShip()){
                return true;
            } else {
                    return false;
            }
            break;
        case down:
            end_.x = (start_.x + length_)-1;
            for(int i=(start_.x); i<(start_.x + length_); i++){
                if(board[i][start_.y-1].isShip() || board[i][start_.y+1].isShip())
                    return true;
            }
            if(board[start_.x-1][start_.y].isShip() || board[end_.x][start_.y].isShip()){
                    return true;
            } else {
                    return false;
            }
            break;
    }
}
void Board::setShipOnBoard(Ship *&ship){
    Point temporary_start = ship->getStart();
    switch (ship->getDirection()) {
        case up:
            for(int i=(temporary_start.y); i>(temporary_start.y - ship->getLength()); i--){
                board[temporary_start.x][i].setShip(ship);
            }
            break;
        case left:
            for(int i=temporary_start.x; i>(temporary_start.x - ship->getLength()); i--){
                board[i][temporary_start.y].setShip(ship);
            }
            break;
        case down:
            for(int i=temporary_start.y; i<(temporary_start.y + ship->getLength()); i++){
                board[temporary_start.x][i].setShip(ship);
            }
            break;
        case right:
            for(int i=temporary_start.x; i<(temporary_start.x + ship->getLength()); i++){
                board[i][temporary_start.y].setShip(ship);
            }
            break;
    }
}

void Board::takeAShotOnBoard(Point &point) {
    board[point.x][point.y].setShot();
}

bool Board::isShip(Point &shot){
    return board[shot.x][shot.y].isShip();
}

Ship* Board::getShip(Point &shot){
    return board[shot.x][shot.y].getShip();
}

bool Board::isShot(Point &point){
    return board[point.x][point.y].isShot();
}

void Board::drawBoard(bool isOwn) {
    const int CWIDTH = 3;
    printHeader();
    printHorizontalLine();
    
    for (int y=0; y<BOARD_SIZE; ++y) {
        std::cout << std::setw(CWIDTH) << std::internal << y << VERTICAL_SEPARATOR;
        for (int x=0; x<BOARD_SIZE; ++x) {
            std::cout << std::setw(CWIDTH)  << board[x][y].getSignToPrint(isOwn) << " " << VERTICAL_SEPARATOR;
        }
        std::cout << std::endl;
        printHorizontalLine();
    }
    std::cout << "\n";
}

void Board::printHorizontalLine() {
    for (int i=0; i<((BOARD_SIZE)*5)+4; ++i)
        std::cout << HORIZONTAL_SEPARATOR;
    std::cout << std::endl;
}

void Board::printHeader() {
    const int CWIDTH = 3;
    std::cout << "\n" << std::setw(CWIDTH) << " " << VERTICAL_SEPARATOR;
    for (int x=0; x<BOARD_SIZE; ++x)
        std::cout << std::setw(CWIDTH) << x << " " << VERTICAL_SEPARATOR;
    std::cout << std::endl;
}
bool Board::isCorrect(Point &point) {
    return board[point.x][point.y].isShip();
}
bool Board::isSunken(Ship *&ship, Point &point){
    int length_ = ship->getLength();
    int shipsFieldHit = 0;
    Direction direct_ = ship->getDirection();
    
    if(direct_ == up || direct_ == down) {
        for(int i=point.y; i<(point.y+length_); i++) {
            if(board[point.x][i].isShip() && board[point.x][i].isShot())
                ++shipsFieldHit;
        }
        
        for(int i=(point.y-1); i>=(point.y-length_); i--) {
            if(board[point.x][i].isShip() && board[point.x][i].isShot())
                ++shipsFieldHit;
        }
    }
    if(direct_ == left || direct_ == right) {
        for(int i=point.x; i<(point.x+length_); i++) {
            if(board[i][point.y].isShip() && board[i][point.y].isShot())
                ++shipsFieldHit;
        }
        for(int i=(point.x-1); i>(point.x-length_); i--) {
            if(board[i][point.y].isShip() && board[i][point.y].isShot())
                ++shipsFieldHit;
        }
    }
    if(shipsFieldHit == length_){
        return true;
        
    } else {
        return false;
    }
}
#endif /* Board_hpp */

