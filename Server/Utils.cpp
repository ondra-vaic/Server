//
// Created by me on 11/14/19.
//
#include <cmath>
#include <vector>

#include "Utils.h"
#include "Vector2D.h"
#include "Board.h"

#define BOARD_DIMENSION 8

bool Utils::CanBeValidJump(Board* board, int x0, int y0, int x1, int y1){
    Vector2D possibleEnemyPosition = CalculateEnemyPosition(x0, y0, x1, y1);
    int possibleEnemy = board->GetFigurine(possibleEnemyPosition.x, possibleEnemyPosition.y);

    if(!Utils::IsInPlayingField(x1, y1))
        return false;

    if (!Utils::IsFigurine(possibleEnemy))
        return false;

    if (Utils::IsPlayer1(possibleEnemy))
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

    return yDelta == 1 && (xDelta == 1 || xDelta == -1) && IsInPlayingField(x1, y1);
}

int Utils::InvertFigurineType(int figurineType){
    switch (figurineType){
        case 1:
            return 3;
        case 2:
            return 4;
        case 3:
            return 1;
        case 4:
            return 2;
        default:
            return 0;
    }
}

Vector2D Utils::CalculateEnemyPosition(int x0, int y0, int x1, int y1){

    Vector2D startPosition{x0, y0};
    Vector2D endPosition{x1, y1};

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

bool Utils::ValidateKingMove(vector<Vector2D>& capturedFigurines, Board* board, int x0, int y0, int x1, int y1){
    Vector2D jumpDelta = {x1 - x0, y1 - y0};
    Vector2D checkPosition = Vector2D{x0, y0};

    int jumpLength = abs(jumpDelta.x);

    for (int i = 1; i < jumpLength; i++)
    {
        checkPosition.x += sign(jumpDelta.x);
        checkPosition.y += sign(jumpDelta.y);

        int checkedFigurine =  board->GetFigurine(checkPosition.x, checkPosition.y);

        if(IsPlayer1(checkedFigurine)){
            return false;
        }

        if(IsEnemy(checkedFigurine)){
            capturedFigurines.push_back(checkPosition);
        }
    }

    return true;

}

bool Utils::BasicMoveConditions(Board* board, int x0, int y0, int x1, int y1){
    int figurine = board->GetFigurine(x0, y0);
    int figurineInWay = board->GetFigurine(x1, y1);

    if (!Utils::IsFigurine(figurine))
        return false;

    if (!Utils::IsEmptyField(figurineInWay))
        return false;

    return Utils::IsDiagonal(x0, y0, x1, y1);
}

int Utils::sign(int n){
    if(n < 0)
        return -1;
    if(n > 0)
        return 1;

    return 0;
}

bool Utils::CanMoveAnywhere(Board* board, int x, int y){
    int figurine = board->GetFigurine(x, y);

    if(IsKing(figurine)){
        return canKingMove(board, x, y);
    }
    return canManMove(board, x, y) || canManJump(board, x, y);
}

bool Utils::canKingMove(Board* board, int x, int y){
    for (int i = 0; i < BOARD_DIMENSION; ++i) {
        for (int j = 0; j < BOARD_DIMENSION; ++j) {
            vector<Vector2D> dummy;
            if(BasicMoveConditions(board, x, y, i, j) && ValidateKingMove(dummy, board, x, y, i, j)){
                return true;
            }
        }
    }

    return false;
}

bool Utils::canManJump(Board* board, int x, int y){
    bool canJumpLeft = BasicMoveConditions(board, x, y, x - 2, y + 2) && CanBeValidJump(board, x, y, x - 2, y + 2);
    bool canJumpRight = BasicMoveConditions(board, x, y, x + 2, y + 2) && CanBeValidJump(board, x, y, x + 2, y + 2);;
    return canJumpLeft || canJumpRight;
}

bool Utils::canManMove(Board* board, int x, int y){
    bool canMoveLeft = BasicMoveConditions(board, x, y, x - 1, y + 1) && CanBeValidWalk(x, y, x - 1, y + 1);
    bool canMoveRight = BasicMoveConditions(board, x, y, x + 1, y + 1) && CanBeValidWalk(x, y, x + 1, y + 1);;
    return canMoveLeft || canMoveRight;
}

bool Utils::IsInPlayingField(int x, int y){return (x >= 0 && x < BOARD_DIMENSION && y >= 0 && y < BOARD_DIMENSION);}
bool Utils::IsEmptyField(int figurine){return figurine == 0;}
bool Utils::IsFigurine(int figurine){return !(figurine == -1 || figurine == 0);}
bool Utils::IsKing(int figurine){return figurine == 2;}
bool Utils::IsPlayer1(int figurine){return figurine == 1 || figurine == 2;}
bool Utils::IsEnemy(int figurine){return IsFigurine(figurine) && !IsPlayer1(figurine);}


//other

void Utils::Error(int code, const char *msg){
    if(code != 0){
        perror(msg);
        exit(1);
    }
}

