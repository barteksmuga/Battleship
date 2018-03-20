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
#define YELLOW   "\033[33m"

#include "GameState.hpp"
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
    void winner(std::string);
    void readFromFile(std::string);
    void finish();
    bool playerMoves(Player*&, Player*&);
    void printMonit(Player*&,std::string);
    void printPlayerBoard(Player*&,Player*&);
    void gameLoop();
    Player *player[2];
    GameState gameState;
    std::string whoWon;
};
Game::Game(){gameState = NOT_STARTED; whoWon = "noName";}
Game::~Game(){}

void Game::startGame() {
    player[0] = new PlayerHuman();
    player[1] = new PlayerAI();
    gameState = STARTED;
}
void Game::setShips() {
    player[0]->createShips();
    player[1]->createShips();
}

void Game::winner(std::string winner) {
    std::cout << "The winner is: " << GREEN << winner << RESET << "!\n";
    system("read -p \"Press any key to continue...\" -n 1 -s");
}

void Game::run() {
    menu();
}

void Game::menu() {
    MenuOptions choice;
    
    std::cout   << "\n\tMENU: "
                << "\n\t1. ABOUT GAME"
                << "\n\t2. GAME RULES"
                << "\n\t3. START GAME"
                << "\n\t4. EXIT"
                << "\n"
                << RED << ">" << YELLOW << ">" << GREEN << "> " << RESET;
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
            gameLoop();
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
void Game::gameLoop() {
    startGame();
    setShips();
    
    Board *enemyBoard = player[1]->getBoard();
    while (gameState != FINISHED) {
        if (!playerMoves(player[0], player[1])) {
            enemyBoard = player[0]->getBoard();
            playerMoves(player[1], player[0]);
        }
    }
    printPlayerBoard(player[0], player[1]);
    winner(whoWon);
}
bool Game::playerMoves(Player *&movingPLayer, Player *&enemy) {
    Point shot;
    Ship *hitShip = nullptr;
    Board *enemyBoard = enemy->getBoard();
    static const int maxHits = Player::getMaxHits()/2;
    
    printPlayerBoard(movingPLayer, enemy);
    
    shot = movingPLayer->takeShot();
    enemyBoard->takeAShotOnBoard(shot);
    
    if (enemy->correctShot(shot)) {
        movingPLayer->hitsIncrement();
        printMonit(movingPLayer, "SHIP HIT");
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        hitShip = enemyBoard->getShip(shot);
    
        if (enemyBoard->isSunken(hitShip, shot)) {
            printMonit(movingPLayer, "SUNKEN SHIP");
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            if (movingPLayer->getHitsCounter() == maxHits) {
                gameState = FINISHED;
                whoWon = movingPLayer->getName();
                return true;
            }
        }
        return playerMoves(movingPLayer, enemy);
    }
    return false;
}

void Game::printPlayerBoard(Player *&movingPlayer, Player *&enemyBoard) {
    if (movingPlayer->getShowOutput()) {
        system("clear");
        printMonit(movingPlayer, "YOUR'S BOARD:");
        movingPlayer->drawPlayerBoard(true);
        printMonit(movingPlayer, "ENEMY'S BOARD:");
        enemyBoard->drawPlayerBoard(false);
    }
}
void Game::printMonit(Player *&player, std::string monit) {
    if (player->getShowOutput()) {
        std::cout << GREEN << monit << RESET << std::endl;
    } else {
        std::cout << RED << monit << RESET << std::endl;
    }
}

void Game::readFromFile(std::string fileName) {
    
    std::string text;
    std::ifstream file;
    file.open(fileName, std::ios::in);
    
    if(!file.good()){
        std::cout << "Cannot open file" << std::endl;
        return;
    }
    for (int i=0;i<200;++i) std::cout <<"-";
    std::cout << std::endl;
    
    while(!file.eof()) {
        std::getline(file,text);
        std::cout << text << std::endl;
    }
    
    for (int i=0;i<200;++i) std::cout <<"-";
    std::cout << std::endl;
    
    file.close();
}
void Game::finish() {
    std::cout << "\n\n\n  Thanks for playing!\n\n";
    std::cout << "  Created by Bartłomiej Smuga\n  MIT License\n  Copyright © 2018 Bartłomiej Smuga.\n\n";
}
#endif /* Game_hpp */

