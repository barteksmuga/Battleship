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
    void takeAShot();
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
PlayerHuman::PlayerHuman(): Player(), ONE_MASTED_SHIPS(0),TWO_MASTED_SHIPS(0),THREE_MASTED_SHIPS(0),FOUR_MASTED_SHIPS(2){}
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
    Board shipsBoard;
    
    oneMastedShips = new Ship *[ONE_MASTED_SHIPS];
    for(int i=0; i<ONE_MASTED_SHIPS; i++){
        shipsBoard.displayShipsOnBoard();
        oneMastedShips[i] = new Ship(1);
        shipsBoard.setShipOnBoard(oneMastedShips[i]);
        std::system("clear");
    }
    
    twoMastedShips = new Ship *[TWO_MASTED_SHIPS];
    for(int i=0; i<TWO_MASTED_SHIPS; i++){
        shipsBoard.displayShipsOnBoard();
        twoMastedShips[i] = new Ship(2);
        shipsBoard.setShipOnBoard(twoMastedShips[i]);
        std::system("clear");
    }
    
    threeMastedShips = new Ship *[THREE_MASTED_SHIPS];
    for(int i=0; i<THREE_MASTED_SHIPS; i++){
        shipsBoard.displayShipsOnBoard();
        threeMastedShips[i] = new Ship(3);
        shipsBoard.setShipOnBoard(threeMastedShips[i]);
        std::system("clear");
    }
    
    fourMastedShips = new Ship *[FOUR_MASTED_SHIPS];
    for(int i=0; i<FOUR_MASTED_SHIPS; i++){
        shipsBoard.displayShipsOnBoard();
        fourMastedShips[i] = new Ship(4);
        shipsBoard.setShipOnBoard(fourMastedShips[i]);
        std::system("clear");
    }
    shipsBoard.displayShipsOnBoard();
}
void PlayerHuman::takeAShot(){
    Board shotsBoard;
    Point shot;
    std::cout << "Where do you wanna take a shot: ";
    std::cin >> shot;
    shotsBoard.takeAShotOnBoard(shot);
    shotsBoard.displayShotsOnBoard();
    std::system("clear");
}
#endif /* PlayerHuman_hpp */
