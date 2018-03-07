//
//  MenuOptions.hpp
//  battleship
//
//  Created by Bartłomiej Smuga on 15/02/2018.
//  Copyright © 2018 Bartłomiej Smuga. All rights reserved.
//

#ifndef MenuOptions_hpp
#define MenuOptions_hpp

#include <iostream>

enum MenuOptions {
    gameDescription = 1,
    rules = 2,
    playGame = 3,
    quit = 4
};
MenuOptions choose(){
    MenuOptions choice;
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
    choice = static_cast<MenuOptions>(decision);
    return choice;
}
#endif /* MenuOptions_hpp */
