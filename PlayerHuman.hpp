//
//  PlayerHuman.hpp
//  battleship
//
//  Created by Bartłomiej Smuga on 24/12/2017.
//  Copyright © 2017 Bartłomiej Smuga
//  Released under the MIT license
//

#ifndef PlayerHuman_hpp
#define PlayerHuman_hpp

#include "Ship.hpp"
#include "Player.hpp"
#include <iostream>
#include <string>
  
class PlayerHuman : public Player {
public:
    PlayerHuman();
    ~PlayerHuman();
    virtual void createShips();
    virtual Point takeShot();
    virtual bool correctShot(Point&);
    virtual Point createStart();
    virtual Direction createDirection();
    void hitsIncrement();
    int getHitsCounter() {return hitsCounter;}
    bool checkShipPosition(Ship*&);
    virtual std::string getName(){return name;};
private:
    Point shotPointsGenerator_ifWasHit(Point&);
    std::string name;
    int hitsCounter;
};
PlayerHuman::PlayerHuman() : Player(), hitsCounter(0) {
    std::cout << "Insert your name: ";
    std::cin >> name;
    std::cout << "Hello " << name << ", let's play a battleship!\n";
}
PlayerHuman::~PlayerHuman(){}

void PlayerHuman::createShips(){
    Point point;
    Direction direct;
    for(int i=0; i<ONE_MASTED_SHIPS; i++){
            board[0]->displayShipsOnBoard();
            point = createStart();
            oneMastedShips[i]->setStart(point);
            std::system("clear");
            board[0]->setShipOnBoard(oneMastedShips[i]);
    }
    for(int i=0; i<TWO_MASTED_SHIPS; i++){
        do{
            board[0]->displayShipsOnBoard();
            point = createStart();
            twoMastedShips[i]->setStart(point);
            direct = createDirection();
            twoMastedShips[i]->setDirection(direct);
            std::system("clear");
        } while(checkShipPosition(twoMastedShips[i]));
        board[0]->setShipOnBoard(twoMastedShips[i]);
    }
    for(int i=0; i<THREE_MASTED_SHIPS; i++){
        do{
            board[0]->displayShipsOnBoard();
            point = createStart();
            threeMastedShips[i]->setStart(point);
            direct = createDirection();
            threeMastedShips[i]->setDirection(direct);
            std::system("clear");
        } while(checkShipPosition(threeMastedShips[i]));
        board[0]->setShipOnBoard(threeMastedShips[i]);
    }
    for(int i=0; i<FOUR_MASTED_SHIPS; i++){
        do{
            board[0]->displayShipsOnBoard();
            point = createStart();
            fourMastedShips[i]->setStart(point);
            direct = createDirection();
            fourMastedShips[i]->setDirection(direct);
            std::system("clear");
        } while(checkShipPosition(fourMastedShips[i]));
        board[0]->setShipOnBoard(fourMastedShips[i]);
    }
    
    board[0]->displayShipsOnBoard();
}
Point PlayerHuman::takeShot(){
    Point shot;
    std::cout << "Where do you wanna take a shot: ";
    std::cin >> shot;
    return shot;
}
bool PlayerHuman::correctShot(Point &shot){
    board[0]->takeAShotOnBoard(shot);
    return board[0]->isShip(shot);
}
Point PlayerHuman::createStart(){
    Point point;
    std::cout << "Insert coordinates for your ship start (y,x): ";
    std::cin >> point;
    return point;
}
Direction PlayerHuman::createDirection(){
    std::cout << "Which way you wanna set Ship:\n1.Left\n2.Up\n3.Right\n4.Down\n";
    Direction direct = setDirection();
    return direct;
}
void PlayerHuman::hitsIncrement(){
   ++hitsCounter;
}
bool PlayerHuman::checkShipPosition(Ship *&ship){
    Point start_ = ship->getStart();
    int length_=ship->getLength();
    Point end_;
    switch (ship->getDirection()) {
        case left:
            end_.y = start_.y - length_;
            if(end_.y < 0){
                std::cout << "Out of board!\n Fix coordinates and direction\n";
                return true;
            } else
                return false;
            break;
        case up:
            end_.x = start_.x - length_;
            if(end_.x < 0){
                std::cout << "Out of board!\n Fix coordinates and direction\n";
                return true;
            } else
                return false;
            break;
        case right:
            end_.y = start_.y + length_;
            if(end_.y > BOARD_SIZE){
                std::cout << "Out of board!\n Fix coordinates and direction\n";
                return true;
            } else
                return false;
            break;
        case down:
            end_.x = start_.x + length_;
            if(end_.x > BOARD_SIZE){
                std::cout << "Out of board!\n Fix coordinates and direction\n";
                return true;
            } else
                return false;
            break;
    }
}
Point PlayerHuman::shotPointsGenerator_ifWasHit(Point &point){
    return Point(0,0);
}

#endif /* PlayerHuman_hpp */
