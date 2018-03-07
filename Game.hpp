//
//  Game.hpp
//  battleship
//
//  Created by Bartłomiej Smuga on 07/01/2018.
//  Copyright © 2017 Bartłomiej Smuga
//  Released under the MIT license
//

#ifndef Game_hpp
#define Game_hpp

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

#include "MenuOptions.hpp"
#include "PlayerAI.hpp"
#include "PlayerHuman.hpp"
#include "Player.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>

class Game{
public:
    Game();
    ~Game();
    void run();
private:
    void startGame();
    void setShips();
    void startShooting();
    void menu();
    void winner();
    void readFromFile(std::string);
    void finish();
    void playerMoves(Player*&, Player*&);
    Player *player[2];
    int player_0_hits;
    int player_1_hits;
};
Game::Game(){player_0_hits = 0; player_1_hits = 0;}
Game::~Game(){}

void Game::startGame() {
    player[0] = new PlayerHuman();
    player[1] = new PlayerAI();
}
void Game::setShips() {
    player[0]->createShips();
    player[1]->createShips();
}
void Game::startShooting() {
    std::system("clear");
    bool humansFlag = false;
    bool AIsFlag = false;
    Point humansShot;
    Point AIsShot;
    int maxHits = Player::maxHits / 2;
    Ship *hitShip = nullptr;
    do {
        player[0]->board[0]->displayShipsOnBoard();
        player[1]->board[0]->displayShotsOnBoard();
        
        humansShot = player[0]->takeShot();
        player[1]->board[0]->takeAShotOnBoard(humansShot);

        if(player[1]->correctShot(humansShot)) {
            std::cout << GREEN << "YOU'VE HIT A SHIP! GO AHEAD!" << RESET << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            humansFlag = true;
            player[0]->hitsIncrement();
            hitShip = player[1]->board[0]->getShip(humansShot);
            if(player[1]->isSunken(hitShip, humansShot)) {
                std::cout << GREEN << "HIT AND SANK! GO AHEAD!" << RESET << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            }
            if(player[0]->getHitsCounter() == maxHits)
                humansFlag = false;
        } else {
            humansFlag = false;
        }
        std::system("clear");
    } while (humansFlag);
    
    do {
        player[0]->board[0]->displayShipsOnBoard();
        player[1]->board[0]->displayShotsOnBoard();

        AIsShot = player[1]->takeShot();
        player[0]->board[0]->takeAShotOnBoard(AIsShot);
        
        if(player[0]->correctShot(AIsShot)) {
            std::cout << RED << "AI HIT YOUR SHIP!" << RESET << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            AIsFlag = true;
            player[1]->hitsIncrement();
            hitShip = player[0]->board[0]->getShip(AIsShot);
            if(player[0]->isSunken(hitShip, AIsShot)) {
                std::cout << RED << "AI HAS SUNKEN YOUR SHIP!" << RESET << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            }
            Point AIsCorrectShot = AIsShot;
            AIsShot = player[1]->shotPointsGenerator_ifWasHit(AIsCorrectShot);
            AIsFlag = player[0]->correctShot(AIsShot);
            player[0]->board[0]->takeAShotOnBoard(AIsShot);
            if(player[1]->getHitsCounter() == maxHits)
                AIsFlag = false;
        }
        std::system("clear");
    } while (AIsFlag);
    
}
void Game::winner() {
    if(player_0_hits > player_1_hits)
        std::cout << GREEN << "Congratulations, " << player[0]->getName() <<"!" << RESET << " You won the battleship!\n";
    else
        std::cout << RED << "Game Over, " << player[1]->getName() << RESET << " won this time. Try again\n";
}
void Game::run() {
    menu();
}
void Game::menu() {
    MenuOptions choice;
    
    std::cout   << "\nMENU: "
                << "\n1. ABOUT GAME"
                << "\n2. GAME RULES"
                << "\n3. START GAME"
                << "\n4. EXIT"
                << "\n~/ ";
    choice = choose();
    
    switch (choice) {
        case gameDescription: {
            readFromFile("description.txt");
            menu();
            break;
        }
        case rules: {
            readFromFile("rules.txt");
            menu();
            break;
        }
        case playGame: {
            startGame();
            setShips();
            int maxHits = Player::maxHits / 2;
            do {
//                startShooting();
                playerMoves(player[0], player[1]);
                player_0_hits = player[0]->getHitsCounter();
                player_1_hits = player[1]->getHitsCounter();
            } while(player_0_hits < maxHits && player_1_hits < maxHits);
            winner();
            menu();
            break;
        }
        case quit: {
            finish();
            return exit(0);
            break;
        }
    }
    
}
void Game::playerMoves(Player *&movingPLayer, Player *&enemy) {
    Point shot;
    Ship *hitShip = nullptr;
    
    movingPLayer->board[0]->displayShipsOnBoard();
    enemy->board[0]->displayShotsOnBoard();
    
    shot = movingPLayer->takeShot();
    enemy->board[0]->takeAShotOnBoard(shot);
    
    if (enemy->correctShot(shot)) {
        movingPLayer->hitsIncrement();
        hitShip = enemy->board[0]->getShip(shot);
        if (enemy->isSunken(hitShip, shot)) {
            std::cout << RED << "SHIP SUNKEN!" << RESET << std::endl;
        }
    }
    system("clear");
}

void Game::readFromFile(std::string fileName) {
    
    std::string text;
    std::ifstream file;
    file.open(fileName, std::ios::in);
    
    if(!file.good()){
        std::cout << "Cannot open file" << std::endl;
        return;
    }
    while(!file.eof()) {
        std::getline(file,text);
        std::cout << text << std::endl;
    }
    file.close();
}
void Game::finish() {
    std::cout << "  Thanks for playing!\n\n";
    std::cout << "  Created by Bartłomiej Smuga\n  MIT License\n  Copyright © 2018 Bartłomiej Smuga.\n\n";
}
#endif /* Game_hpp */

