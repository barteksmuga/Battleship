//
//  Point.hpp
//  battleship
//
//  Created by Bartłomiej Smuga on 15/12/2017.
//  Copyright © 2017 Bartłomiej Smuga
//  Released under the MIT license
//

#ifndef Point_hpp
#define Point_hpp

#include <iostream>
class Point;
std::istream &operator >>(std::istream&,Point&);
  
class Point{
public:
    Point();
    Point(int,int);
    int x,y;
    friend std::istream &operator >>(std::istream&,Point&);
    bool operator ==(const Point&);
};
Point::Point(){}
Point::Point(int X, int Y): x(X), y(Y){}

std::istream &operator >>(std::istream &input, Point &point){
    input >> point.x >> point.y;
    return input;
}
bool Point::operator ==(const Point &point){
    if((this->x == point.x) && (this->y == point.y))
        return true;
    else
        return false;
}

#endif /* Point_hpp */
