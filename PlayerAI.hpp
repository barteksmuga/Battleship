//
//  PlayerAI.hpp
//  battleship
//
//  Created by Bartłomiej Smuga on 05/01/2018.
//  Copyright © 2018 Bartłomiej Smuga. All rights reserved.
//

#ifndef PlayerAI_hpp
#define PlayerAI_hpp

#include <iostream>
#include <ctime>
#include <vector>
  
class PlayerAI : public Player {
public:
    PlayerAI();
    ~PlayerAI();
    virtual void createShips();
    virtual Point takeShot();
    virtual bool correctShot(Point&);
    virtual Point createStart();
    virtual Direction createDirection();
    Point startPointsGenerator();
    Point shotPointsGenerator();
    bool isPointTaken(Point&);
    bool isPointShot(Point&);
    void hitsIncrement();
    int getHitsCounter() {return hitsCounter;}
    bool checkShipPosition(Ship*&);
    Point shotPointsGenerator_ifWasHit(Point&);
    virtual std::string getName(){return name;}
private:
    std::string name;
    std::vector<Point> chosenStartPoints;
    std::vector<Point> shotPoints;
    int hitsCounter;
};
PlayerAI::PlayerAI() : Player(), hitsCounter(0), name("AI") {}
PlayerAI::~PlayerAI(){}

void PlayerAI::createShips(){
    Point point;
    Direction direct;
    bool state = false;
    bool state1 = false;
    for(int i=0; i<ONE_MASTED_SHIPS; ++i){
        do {
            point = createStart();
            oneMastedShips[i]->setStart(point);
            direct = createDirection();
            oneMastedShips[i]->setDirection(direct);
        } while (board[0]->checkAroundShip(oneMastedShips[i]));
        board[0]->setShipOnBoard(oneMastedShips[i]);
    }
    for(int i=0; i<TWO_MASTED_SHIPS; i++){
        do {
            point = createStart();
            twoMastedShips[i]->setStart(point);
            direct = createDirection();
            twoMastedShips[i]->setDirection(direct);
        } while(checkShipPosition(twoMastedShips[i]) || board[0]->checkAroundShip(twoMastedShips[i]));
        board[0]->setShipOnBoard(twoMastedShips[i]);
    }
    for(int i=0; i<THREE_MASTED_SHIPS; i++){
        do {
            point = createStart();
            threeMastedShips[i]->setStart(point);
            direct = createDirection();
            threeMastedShips[i]->setDirection(direct);
        } while (checkShipPosition(threeMastedShips[i]) || board[0]->checkAroundShip(threeMastedShips[i]));
        board[0]->setShipOnBoard(threeMastedShips[i]);
    }
    for(int i=0; i<FOUR_MASTED_SHIPS; i++){
        do {
            point = createStart();
            fourMastedShips[i]->setStart(point);
            direct = createDirection();
            fourMastedShips[i]->setDirection(direct);
            state = board[0]->checkAroundShip(fourMastedShips[i]);
            state1 = checkShipPosition(fourMastedShips[i]);
        } while (checkShipPosition(fourMastedShips[i]) || board[0]->checkAroundShip(fourMastedShips[i]));
        board[0]->setShipOnBoard(fourMastedShips[i]);
    }
}
Point PlayerAI::takeShot(){
    Point shot;
    shot = shotPointsGenerator();
    board[1]->takeAShotOnBoard(shot);
    return shot;
}
bool PlayerAI::correctShot(Point &shot){
    return board[0]->isShip(shot);
}
Point PlayerAI::createStart(){
    Point point = startPointsGenerator();
    return point;
}
Direction PlayerAI::createDirection(){
    Direction direct = randomDirection(4,1);
    return direct;
}
Point PlayerAI::startPointsGenerator(){
    srand(time(NULL));
    int x,y;
    x = rand()%10;
    y = rand()%10;
    Point point(x,y);
    if(isPointTaken(point)){
        while(isPointTaken(point)){
            x = rand()%10;
            y = rand()%10;
            point.x = x;
            point.y = y;
        }
    }
    chosenStartPoints.push_back(point);
    return point;
}
Point PlayerAI::shotPointsGenerator(){
    srand(time(NULL));
    int x,y;
    x = rand()%10;
    y = rand()%10;
    Point point(x,y);
    if(isPointShot(point)){
        while(isPointShot(point)){
            x = rand()%10;
            y = rand()%10;
            point.x = x;
            point.y = y;
        }
    }
    shotPoints.push_back(point);
    return point;
}
Point PlayerAI::shotPointsGenerator_ifWasHit(Point &shot){
    Point possibleShots[4];
    possibleShots[0].x = shot.x + 1; possibleShots[0].y = shot.y;
    possibleShots[1].x = shot.x - 1; possibleShots[1].y = shot.y;
    
    possibleShots[2].x = shot.x; possibleShots[2].y = shot.y + 1;
    possibleShots[3].x = shot.x; possibleShots[3].y = shot.y - 1;
    
    Point point = possibleShots[rand()%4];
    if(isPointShot(point)){
        while (isPointShot(point)){
            point = possibleShots[rand()%4];
        }
    }
    shotPoints.push_back(point);
    return point;
}
bool PlayerAI::isPointTaken(Point &point){
    for(int i=0; i<chosenStartPoints.size(); i++){
        if(point == chosenStartPoints[i])
            return true;
    }
    return false;
}
bool PlayerAI::isPointShot(Point &point){
    for(int i=0; i<shotPoints.size(); i++){
        if(point == shotPoints[i])
            return true;
    }
    return false;
}
void PlayerAI::hitsIncrement() {++hitsCounter;}
bool PlayerAI::checkShipPosition(Ship *&ship){
    Point start_ = ship->getStart();
    int length_=ship->getLength();
    Point end_;
    switch (ship->getDirection()) {
        case left:
            end_.y = start_.y - length_;
            if(end_.y < 0)
                return true;
            else
                return false;
            break;
        case up:
            end_.x = start_.x - length_;
            if(end_.x < 0)
                return true;
            else
                return false;
            break;
        case right:
            end_.y = start_.y + length_;
            if(end_.y > BOARD_SIZE)
                return true;
            else
                return false;
            break;
        case down:
            end_.x = start_.x + length_;
            if(end_.x > BOARD_SIZE)
                return true;
            else
                return false;
            break;
    }
}

#endif /* PlayerAI_hpp */
