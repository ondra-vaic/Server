//
// Created by me on 11/14/19.
//

#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H


#include "Vector2D.h"
#include "Board.h"

using namespace std;


class Utils {

public:
    static bool CanBeValidJump(Board* board, int x0, int y0, int x1, int y1);
    static bool IsDiagonal(int x0, int y0, int x1, int y1);
    static bool CanBeValidWalk(int x0, int y0, int x1, int y1);
    static Vector2D CalculateEnemyPosition(int x0, int y0, int x1, int y1);
    static bool ValidateKingMove(const vector<int>& capturedFigurines, int x0, int y0, int x1, int y1);
};


#endif //SERVER_UTILS_H
