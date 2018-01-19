//
//  Direction.hpp
//  battleship
//
//  Created by Bartłomiej Smuga on 15/12/2017.
//  Copyright © 2017 Bartłomiej Smuga. All rights reserved.
//


#ifndef Direction_hpp
#define Direction_hpp

#include <iostream>

enum Direction {left = 1,up = 2,right = 3,down = 4};

Direction setDirection(){
    Direction direction;
    int decision;
    bool flag = false;
    do {
        std::cin >> decision;
        if(decision > 4){
            std::cout << "Insert number between 1-4!!!\n";
            flag = true;
        } else
            flag = false;
    } while(flag);
    direction = static_cast<Direction>(decision);
    return direction;
}

Direction randomDirection(int numberOfElements, int firstElement){
    srand(time(NULL));
    Direction direct;
    direct = static_cast<Direction>(rand() % numberOfElements + firstElement);
    return direct;
}

#endif /* Direction_hpp */
