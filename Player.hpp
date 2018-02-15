//
//  Player.hpp
//  battleship
//
//  Created by Bartłomiej Smuga on 24/12/2017.
//  Copyright © 2017 Bartłomiej Smuga
//  Released under the MIT license
//

#ifndef Player_hpp
#define Player_hpp

#include <iostream>
#include "Ship.hpp"
#include "Board.hpp"
const int ONE_MASTED_SHIPS = 4;
const int TWO_MASTED_SHIPS = 3;
const int THREE_MASTED_SHIPS = 2;
const int FOUR_MASTED_SHIPS = 1;
  
class Player{
public:
    friend class Game;
    Player();
    virtual ~Player();
    virtual void createShips()=0;
    virtual Point takeShot()=0;
    virtual bool correctShot(Point&)=0;
    virtual Point createStart()=0;
    virtual Direction createDirection()=0;
    virtual void hitsIncrement()=0;
    virtual int getHitsCounter()=0;
    virtual Point shotPointsGenerator_ifWasHit(Point&)=0;
    virtual std::string getName()=0;
protected:
    Board *board[2];
    Ship *oneMastedShips[ONE_MASTED_SHIPS];
    Ship *twoMastedShips[TWO_MASTED_SHIPS];
    Ship *threeMastedShips[THREE_MASTED_SHIPS];
    Ship *fourMastedShips[FOUR_MASTED_SHIPS];
    static int maxHits;
};
int Player::maxHits = 0;
Player::Player(){
    for(int i=0;i<2;i++)
        board[i] = new Board;
    for(int i=0; i<ONE_MASTED_SHIPS; i++){
        oneMastedShips[i] = new Ship(1);
        maxHits += 1;
    }
    for(int i=0; i<TWO_MASTED_SHIPS; i++){
        twoMastedShips[i] = new Ship(2);
        maxHits += 2;
    }
    for(int i=0; i<THREE_MASTED_SHIPS; i++){
        threeMastedShips[i] = new Ship(3);
        maxHits += 3;
    }
    for(int i=0; i<FOUR_MASTED_SHIPS; i++){
        fourMastedShips[i] = new Ship(4);
        maxHits += 4;
    }
}
Player::~Player(){
    delete oneMastedShips[ONE_MASTED_SHIPS];
    delete twoMastedShips[TWO_MASTED_SHIPS];
    delete threeMastedShips[THREE_MASTED_SHIPS];
    delete fourMastedShips[FOUR_MASTED_SHIPS];
    delete board[2];
}

#endif /* Player_hpp */
