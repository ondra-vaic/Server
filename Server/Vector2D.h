//
// Created by me on 11/15/19.
//

#ifndef SERVER_VECTOR2D_H
#define SERVER_VECTOR2D_H


struct Vector2D {
    int x;
    int y;
};

Vector2D operator+(Vector2D v0, Vector2D v1){
    return Vector2D{v0.x + v1.x, v0.y + v1.y};
}

Vector2D operator-(Vector2D v0, Vector2D v1){
    return Vector2D{v0.x - v1.x, v0.y - v1.y};
}


#endif //SERVER_VECTOR2D_H
