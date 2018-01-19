//  main.cpp
//  battleship
//
//  Created by Bartłomiej Smuga on 15/12/2017.
//  Copyright © 2017 Bartłomiej Smuga. All rights reserved.
//

#include <iostream>
#include "Point.hpp"
#include "Field.hpp"
#include "Ship.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include "PlayerHuman.hpp"
#include "PlayerAI.hpp"
#include "Game.hpp"

#define EXIT_SUCCESS 0

int main() {
    {
        Game game;
        game.run();
    }

    return EXIT_SUCCESS;
}
