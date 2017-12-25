
//  main.cpp
//  battleship
//
//  Created by Bartłomiej Smuga on 15/12/2017.
//  Copyright © 2017 Bartłomiej Smuga. All rights reserved.
//
#include "PlayerHuman.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Field.hpp"
#include "Ship.hpp"
#include "Point.hpp"
#include <iostream>

#define EXIT_SUCCES 0

int main(){
    {
    PlayerHuman player;
    
    player.setShips();
        player.takeAShot();
    }
    std::cout << "SHIPS: " << Ship::getCounter() << std::endl;
    
    return EXIT_SUCCESS;
}
