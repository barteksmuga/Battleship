//
//  Player.hpp
//  battleship
//
//  Created by Bartłomiej Smuga on 24/12/2017.
//  Copyright © 2017 Bartłomiej Smuga
//  Released under the MIT license
//

#ifndef Player_hpp
#define Player_hpp

#include <iostream>
#include "Ship.hpp"
#include "Board.hpp"

const int ONE_MASTED_SHIPS = 4;
const int TWO_MASTED_SHIPS = 3;
const int THREE_MASTED_SHIPS = 2;
const int FOUR_MASTED_SHIPS = 1;
  
class Player{
public:
    friend class Game;
    Player();
    virtual ~Player();
    virtual void createShips()=0;
    virtual Point takeShot()=0;
    virtual bool correctShot(Point&)=0;
    virtual Point createStart()=0;
    virtual Direction createDirection()=0;
    virtual void hitsIncrement()=0;
    virtual int getHitsCounter()=0;
    virtual std::string getName()=0;
    virtual Point shotPointsGenerator_ifWasHit(Point&)=0;
    virtual bool isSunken(Ship*&,Point&);
protected:
    Board *board[2];
    Ship *oneMastedShips[ONE_MASTED_SHIPS];
    Ship *twoMastedShips[TWO_MASTED_SHIPS];
    Ship *threeMastedShips[THREE_MASTED_SHIPS];
    Ship *fourMastedShips[FOUR_MASTED_SHIPS];
    static int maxHits;
};
int Player::maxHits = 0;
Player::Player(){
    for(int i=0;i<2;i++)
        board[i] = new Board;
    for(int i=0; i<ONE_MASTED_SHIPS; i++){
        oneMastedShips[i] = new Ship(1);
        maxHits += 1;
    }
    for(int i=0; i<TWO_MASTED_SHIPS; i++){
        twoMastedShips[i] = new Ship(2);
        maxHits += 2;
    }
    for(int i=0; i<THREE_MASTED_SHIPS; i++){
        threeMastedShips[i] = new Ship(3);
        maxHits += 3;
    }
    for(int i=0; i<FOUR_MASTED_SHIPS; i++){
        fourMastedShips[i] = new Ship(4);
        maxHits += 4;
    }
}
Player::~Player(){
    delete oneMastedShips[ONE_MASTED_SHIPS];
    delete twoMastedShips[TWO_MASTED_SHIPS];
    delete threeMastedShips[THREE_MASTED_SHIPS];
    delete fourMastedShips[FOUR_MASTED_SHIPS];
    delete board[2];
}
bool Player::isSunken(Ship *&ship, Point &point){
    /* musze sprawdzac inaczej pola. w zaleznosci od strzelonego punktu w dol/gore/lewo/prawo, bo sprawdzam pola od startu, gdzie nie zawsze zaczynam trafiac!*/
    if(ship == nullptr)
        return false;
    
    int length_ = ship->getLength();
//    Point start_ = ship->getStart();
    Point shot_point = point;
    Point tmp_point(0,0);
    int shipsFieldHit = 0;
    Direction direct_ = ship->getDirection();
    
    if(direct_ == left || direct_ == right) {
        for(int i=shot_point.y; i<(shot_point.y+length_); i++) {
            tmp_point.x = shot_point.x;
            tmp_point.y = i;
            if(board[0]->isShip(tmp_point) && board[0]->isShot(tmp_point))
                ++shipsFieldHit;
        }
        for(int i=(shot_point.y-1); i>=(shot_point.y-length_); i--) {
            tmp_point.x = shot_point.x;
            tmp_point.y = i;
            if(board[0]->isShip(tmp_point) && board[0]->isShot(tmp_point))
                ++shipsFieldHit;
        }
    }
    if(direct_ == up || direct_ == down) {
        for(int i=shot_point.x; i<(shot_point.x+length_); i++) {
            tmp_point.x = i;
            tmp_point.y = shot_point.y;
            if(board[0]->isShip(tmp_point) && board[0]->isShot(tmp_point))
                ++shipsFieldHit;
        }
        for(int i=(shot_point.x-1); i>(shot_point.x-length_); i--) {
            tmp_point.x = i;
            tmp_point.y = shot_point.y;
            if(board[0]->isShip(tmp_point) && board[0]->isShot(tmp_point))
                ++shipsFieldHit;
        }
    }
    if(shipsFieldHit == length_){
        return true;
        
    } else {
        return false;
    }
//    if(length_ > 1) {
//        switch(ship->getDirection()){
//            case left:
//                for(int i=(start_.y); i>(start_.y - length_); i--) {
//                    point.x = start_.x;
//                    point.y = i;
//                    if(board[0]->isShot(point))
//                        ++shipsFieldHit;
//
//                }
//                if(shipsFieldHit == length_)
//                    return true;
//
//                return false;
//                break;
//            case up:
//                for(int i=(start_.x); i>(start_.x-length_); i--){
//                    point.x = i;
//                    point.y = start_.y;
//                    if(board[0]->isShot(point))
//                        ++shipsFieldHit;
//
//                }
//                if(shipsFieldHit == length_)
//                    return true;
//
//                return false;
//
//                break;
//            case right:
//                for(int i=(start_.y); i<(start_.y + length_); i++){
//                    point.x = start_.x;
//                    point.y = i;
//                    if(board[0]->isShot(point))
//                        ++shipsFieldHit;
//
//                }
//                if(shipsFieldHit == length_)
//                    return true;
//
//                return false;
//
//                break;
//            case down:
//                for(int i=(start_.x); i<(start_.x + length_); i++){
//                    point.x = i;
//                    point.y = start_.y;
//                    if(board[0]->isShot(point))
//                        ++shipsFieldHit;
//
//                }
//                if(shipsFieldHit == length_)
//                    return true;
//
//                return false;
//
//                break;
//        }
//    } else {
//        return true;
//    }
}
#endif /* Player_hpp */
