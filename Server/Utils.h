//
// Created by me on 11/14/19.
//

#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H

#include<vector>
#include <algorithm>
#include "Vector2D.h"
#include "Board.h"

using namespace std;


class Utils {

private:
    static int sign(int n);
    static bool canKingMove(Board* board, int x, int y);
    static bool canManMove(Board* board, int x, int y);
    static bool canManJump(Board* board, int x, int y);

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
    static bool CanMoveAnywhere(Board* board, int x, int y);
    static bool BasicMoveConditions(Board* board, int x0, int y0, int x1, int y1);
    static int InvertFigurineType(int figurineType);

    template <typename T, typename L>
    static void RemoveIf(vector<T> vector, L condition){
        vector.erase(std::remove_if(vector.begin(), vector.end(), condition, vector.end()));
    }

    static void Error(int code, const char *msg);
};


#endif //SERVER_UTILS_H
