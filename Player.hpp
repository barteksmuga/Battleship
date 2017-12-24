//
//  Player.hpp
//  battleship
//
//  Created by Bartłomiej Smuga on 24/12/2017.
//  Copyright © 2017 Bartłomiej Smuga. All rights reserved.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <iostream>

class Player{
public:
    Player();
    virtual ~Player() = 0;
    virtual void setShips() = 0;
protected:
    std::string name;
};
Player::Player(){
    std::cout << "Insert your name: ";
    std::cin >> name;
    std::cout << "Hello " << name << ", let's play a battleship!\n";
}
Player::~Player(){}
#endif /* PLAYER_HPP */
