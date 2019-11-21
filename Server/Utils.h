//
// Created by me on 11/14/19.
//

#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H

#include<vector>
#include "Vector2D.h"
#include "Board.h"

using namespace std;


class Utils {

public:
    static bool CanBeValidJump(Board* board, int x0, int y0, int x1, int y1);
    static bool IsDiagonal(int x0, int y0, int x1, int y1);
    static bool CanBeValidWalk(int x0, int y0, int x1, int y1);
    static Vector2D CalculateEnemyPosition(int x0, int y0, int x1, int y1);
    static bool ValidateKingMove(vector<Vector2D>& capturedFigurines, Board* board, int x0, int y0, int x1, int y1);
    static bool IsFigurine(int figurine);
    static bool IsKing(int figurine);
    static bool IsPlayer1(int figurine);
    static bool IsEmptyField(int figurine);
    static bool IsInPlayingField(int x, int y);
    static bool IsEnemy(int figurine);
    static int sign(int n);
    static bool CanMoveAnywhere(int** board, int x, int y);

};


#endif //SERVER_UTILS_H
