//
//  PlayerHuman.hpp
//  battleship
//
//  Created by Bartłomiej Smuga on 24/12/2017.
//  Copyright © 2017 Bartłomiej Smuga. All rights reserved.
//

#ifndef PlayerHuman_hpp
#define PlayerHuman_hpp

#include "Board.hpp"
#include "Ship.hpp"
#include "Player.hpp"
#include <iostream>
#include <string>
#include <curses.h>

class PlayerHuman: public Player{
public:
    PlayerHuman();
    ~PlayerHuman();
    void setShips();
private:
    const int ONE_MASTED_SHIPS;
    const int TWO_MASTED_SHIPS;
    const int THREE_MASTED_SHIPS;
    const int FOUR_MASTED_SHIPS;
    Ship **oneMastedShips;
    Ship **twoMastedShips;
    Ship **threeMastedShips;
    Ship **fourMastedShips;
};
PlayerHuman::PlayerHuman(): Player(), ONE_MASTED_SHIPS(4),TWO_MASTED_SHIPS(3),THREE_MASTED_SHIPS(2),FOUR_MASTED_SHIPS(1){}
PlayerHuman::~PlayerHuman(){
    for(int i=0; i<ONE_MASTED_SHIPS; i++)
        delete oneMastedShips[i];
    delete [] oneMastedShips;
    
    for(int i=0; i<TWO_MASTED_SHIPS; i++)
        delete twoMastedShips[i];
    delete [] twoMastedShips;
    
    for(int i=0; i<THREE_MASTED_SHIPS; i++)
        delete threeMastedShips[i];
    delete [] threeMastedShips;
    
    for(int i=0; i<FOUR_MASTED_SHIPS; i++)
        delete fourMastedShips[i];
    delete [] fourMastedShips;
    
}
void PlayerHuman::setShips(){
    Board board;
    
    oneMastedShips = new Ship *[ONE_MASTED_SHIPS];
    for(int i=0; i<ONE_MASTED_SHIPS; i++){
        board.displayBoard();
        oneMastedShips[i] = new Ship(1);
        board.setShipOnBoard(oneMastedShips[i]);
        std::system("clear");
    }
    
    twoMastedShips = new Ship *[TWO_MASTED_SHIPS];
    for(int i=0; i<TWO_MASTED_SHIPS; i++){
        board.displayBoard();
        twoMastedShips[i] = new Ship(2);
        board.setShipOnBoard(twoMastedShips[i]);
        std::system("clear");
    }
    
    threeMastedShips = new Ship *[THREE_MASTED_SHIPS];
    for(int i=0; i<THREE_MASTED_SHIPS; i++){
        board.displayBoard();
        threeMastedShips[i] = new Ship(3);
        board.setShipOnBoard(threeMastedShips[i]);
        std::system("clear");
    }
    
    fourMastedShips = new Ship *[FOUR_MASTED_SHIPS];
    for(int i=0; i<FOUR_MASTED_SHIPS; i++){
        board.displayBoard();
        fourMastedShips[i] = new Ship(4);
        board.setShipOnBoard(fourMastedShips[i]);
        std::system("clear");
    }
    board.displayBoard();
}
#endif /* PlayerHuman_hpp */
