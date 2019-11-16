//
// Created by me on 11/14/19.
//
#include <cmath>
#include <vector>

#include "Utils.h"
#include "Vector2D.h"
#include "Board.h"


bool Utils::ValidateKingMove(const vector<int>& capturedFigurines, int x0, int y0, int x1, int y1){
    return false;
}

bool Utils::CanBeValidJump(Board* board, int x0, int y0, int x1, int y1){
    Vector2D possibleEnemyPosition = CalculateEnemyPosition(x0, y0, x1, y1);
    int possibleEnemy = board->GetFigure(possibleEnemyPosition.x, possibleEnemyPosition.y);

    if (!board->IsFigurine(possibleEnemy))
        return false;

    if (board->IsPlayer1(possibleEnemy))
        return false;

    //if enemy is one diagonally then I can jump over him
    return CanBeValidWalk(x0, y0, possibleEnemyPosition.x, possibleEnemyPosition.y);
}

bool Utils::IsDiagonal(int x0, int y0, int x1, int y1){
    return abs(x0 - x1) == abs(y0 - y1);
}

bool Utils::CanBeValidWalk(int x0, int y0, int x1, int y1){

    int xDelta = x1 - x0;
    int yDelta = y1 - y0;

    return yDelta == 1 && (xDelta == 1 || xDelta == -1);
}


Vector2D Utils::CalculateEnemyPosition(int x0, int y0, int x1, int y1){

    Vector2D startPosition{x0, y0};
    Vector2D endPosition{x0, y0};

    Vector2D jumpDelta = endPosition - startPosition;
    Vector2D position = startPosition;

    if (jumpDelta.x == 2)
    {
        position.x += jumpDelta.x - 1;
    }
    else
    {
        position.x += jumpDelta.x + 1;
    }
    position.y += jumpDelta.y - 1;

    return position;
}
