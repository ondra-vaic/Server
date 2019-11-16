//
// Created by me on 11/15/19.
//

#ifndef SERVER_VECTOR2D_H
#define SERVER_VECTOR2D_H


struct Vector2D {
    int x;
    int y;

    Vector2D operator+(Vector2D v){
        return Vector2D{this->x + v.x, this->y + v.y};
    }

    Vector2D operator-(Vector2D v){
        return Vector2D{this->x - v.x, this->y - v.y};
    }

};



#endif //SERVER_VECTOR2D_H
