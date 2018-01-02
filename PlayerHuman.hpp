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
    Point takeAShot();
private:
    Board playerBoard;
    const int ONE_MASTED_SHIPS;
    const int TWO_MASTED_SHIPS;
    const int THREE_MASTED_SHIPS;
    const int FOUR_MASTED_SHIPS;
    Ship **oneMastedShips;
    Ship **twoMastedShips;
    Ship **threeMastedShips;
    Ship **fourMastedShips;
};
PlayerHuman::PlayerHuman(): Player(), ONE_MASTED_SHIPS(0),TWO_MASTED_SHIPS(0),THREE_MASTED_SHIPS(0),FOUR_MASTED_SHIPS(1){}
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
    
    oneMastedShips = new Ship *[ONE_MASTED_SHIPS];
    for(int i=0; i<ONE_MASTED_SHIPS; i++){
        playerBoard.displayShipsOnBoard();
        oneMastedShips[i] = new Ship(1);
        playerBoard.setShipOnBoard(oneMastedShips[i]);
        std::system("clear");
    }
    
    twoMastedShips = new Ship *[TWO_MASTED_SHIPS];
    for(int i=0; i<TWO_MASTED_SHIPS; i++){
        playerBoard.displayShipsOnBoard();
        twoMastedShips[i] = new Ship(2);
        playerBoard.setShipOnBoard(twoMastedShips[i]);
        std::system("clear");
    }
    
    threeMastedShips = new Ship *[THREE_MASTED_SHIPS];
    for(int i=0; i<THREE_MASTED_SHIPS; i++){
        playerBoard.displayShipsOnBoard();
        threeMastedShips[i] = new Ship(3);
        playerBoard.setShipOnBoard(threeMastedShips[i]);
        std::system("clear");
    }
    
    fourMastedShips = new Ship *[FOUR_MASTED_SHIPS];
    for(int i=0; i<FOUR_MASTED_SHIPS; i++){
        playerBoard.displayShipsOnBoard();
        fourMastedShips[i] = new Ship(4);
        playerBoard.setShipOnBoard(fourMastedShips[i]);
        std::system("clear");
    }
    playerBoard.displayShipsOnBoard();
}
Point PlayerHuman::takeAShot(){
    bool flag = true;
    Point shot;
    while(flag){
        playerBoard.displayShipsOnBoard();
        gameBoard.displayShotsOnBoard();
        std::cout << "Where do you wanna take a shot: ";
        std::cin >> shot;
        gameBoard.takeAShotOnBoard(shot);
        if(correctShot(shot))
            std::cout << "You've already hit a ship. Go ahead!\n";
        else
            flag = false;
    }
    std::system("clear");
    playerBoard.displayShipsOnBoard();
    gameBoard.displayShotsOnBoard();
    return shot;
}
#endif /* PlayerHuman_hpp */
