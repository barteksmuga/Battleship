//
//  Point.hpp
//  battleship
//
//  Created by Bartłomiej Smuga on 15/12/2017.
//  Copyright © 2017 Bartłomiej Smuga. All rights reserved.
//

#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
class Point;
std::istream &operator >>(std::istream&,Point&);

class Point{
public:
    int x,y;
    friend std::istream &operator >>(std::istream&,Point&);
    Point(int X, int Y): x(X), y(Y){}
    Point(){}
    Point &operator --();
    Point &operator --(int);
};
Point & Point::operator --(){
    x -= 1;
    y -= 1;
    return *this;
}
Point & Point::operator --(int){
    x -= 1;
    y -= 1;
    return *this;
}
//************************************************************
std::istream &operator >>(std::istream &input, Point &point){
    input >> point.x >> point.y;
    return input;
}
#endif /* POINT_HPP */
