//
//  Game.hpp
//  battleship
//
//  Created by Bartłomiej Smuga on 07/01/2018.
//  Copyright © 2018 Bartłomiej Smuga. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp
 
#include "PlayerAI.hpp"
#include "PlayerHuman.hpp"
#include "Player.hpp"
#include <iostream>

class Game{
public:
    Game();
    ~Game();
    void startGame();
    void setShips();
    void startShooting();
    void winner();
    void run();
private:
    Player *player[2];
    int player_0_hits;
    int player_1_hits;
};
Game::Game(){player_0_hits = 0; player_1_hits = 0;}
Game::~Game(){}

void Game::startGame(){
    player[0] = new PlayerHuman();
    player[1] = new PlayerAI();
}
void Game::setShips(){
    player[0]->createShips();
    player[1]->createShips();
}
void Game::startShooting(){
    std::system("clear");
    player[0]->board[0]->displayShipsOnBoard();
    player[1]->board[0]->displayShotsOnBoard();
    Point humansShot = player[0]->takeShot();
    player[1]->board[0]->takeAShotOnBoard(humansShot);
    std::system("clear");
    player[0]->board[0]->displayShipsOnBoard();
    player[1]->board[0]->displayShotsOnBoard();
    while(player[1]->correctShot(humansShot)){
        player[0]->hitsIncrement();
        humansShot = player[0]->takeShot();
        player[1]->board[0]->takeAShotOnBoard(humansShot);
        std::system("clear");
        player[0]->board[0]->displayShipsOnBoard();
        player[1]->board[0]->displayShotsOnBoard();
    }

    Point AIsShot = player[1]->takeShot();
    player[0]->board[0]->takeAShotOnBoard(AIsShot);
    std::system("clear");
    player[0]->board[0]->displayShipsOnBoard();
    player[1]->board[0]->displayShotsOnBoard();
    while (player[0]->correctShot(AIsShot)){
        player[1]->hitsIncrement();
        Point AIsCorrectShot = AIsShot;
        AIsShot = player[1]->shotPointsGenerator_ifWasHit(AIsCorrectShot);
        player[0]->board[0]->takeAShotOnBoard(AIsShot);
        std::system("clear");
        player[0]->board[0]->displayShipsOnBoard();
        player[1]->board[0]->displayShotsOnBoard();
    }
}
void Game::winner(){
    if(player_0_hits > player_1_hits)
        std::cout << "Congratulations, " << player[0]->getName() <<"! You won the battleship!\n";
    else
        std::cout << "Game Over, " << player[1]->getName() << "won this time. Try again\n";
    
    std::cout << "//  Created by Bartłomiej Smuga\n//  Copyright © 2018 Bartłomiej Smuga. All rights reserved.";
}
void Game::run(){
    
    startGame();
    setShips();
    int maxHits = Player::maxHits / 2;
    do {
        startShooting();
        player_0_hits = player[0]->getHitsCounter();
        player_1_hits = player[1]->getHitsCounter();
    } while(player_0_hits < maxHits && player_1_hits < maxHits);
    winner();
}
#endif /* Game_hpp */

