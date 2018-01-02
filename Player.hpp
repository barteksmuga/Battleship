//
//  Player.hpp
//  battleship
//
//  Created by Bartłomiej Smuga on 24/12/2017.
//  Copyright © 2017 Bartłomiej Smuga. All rights reserved.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cmath>
#include <string>
#include <iostream>
#include "Board.hpp"

class Player{
public:
    Player();
    virtual ~Player() = 0;
    virtual void setShips() = 0;
    virtual Point takeAShot() = 0;
    virtual bool correctShot(Point&);
    void surprisePrint();
protected:
    std::string name;
    Board gameBoard;
};
Player::Player(){
    std::cout << "Insert your name: ";
    std::cin >> name;
    if(name == "Monika" || name == "monika" || name == "Monia" ||name == "monia")
        surprisePrint();
    else
        std::cout << "Hello " << name << ", let's play a battleship!\n";
}
Player::~Player(){}
bool Player::correctShot(Point &shot){
    if(gameBoard.isShipOnField(shot))
        return true;
    else
        return false;        
}
void Player::surprisePrint(){
    double x,y;
    double size=10;
    for (x=0; x<size; x++){
        for (y=0;y<=4*size;y++){
            double dist1 = sqrt( pow(x-size,2) + pow(y-size,2) );
            double dist2 = sqrt( pow(x-size,2) + pow(y-3*size,2) );
            
            if (dist1 < size + 0.5 || dist2 < size + 0.5 )
                std::cout<<"V";
            else
                std::cout<<" ";
        }
        std::cout<<std::endl;
    }
    for(x=1; x<2*size; x++){
        for(y=0;y<x;y++)
            std::cout<<" ";
        
        for (y=0; y<(4*size+1-2*x); y++)
            std::cout<<"V";
        
        std::cout<<std::endl;
    }
}
#endif /* PLAYER_HPP */
