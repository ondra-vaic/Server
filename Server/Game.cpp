//
// Created by me on 11/5/19.
//


#include <vector>
#include <cmath>
#include <tuple>

#include "Game.h"
#include "Vector2D.h"
#include "Utils.h"

using namespace std;

Game::Game(int player1, int player2, Board* board) : player1(player1),
player2(player2), board(board), player1Turn(true), hasMoved(false){}

int Game::GetCurrentPlayer() {
    return player1Turn ? player1 : player2;
}

int Game::GetOtherPlayer() {
    return player1Turn ?  player2 : player1;
}

void Game::SetPlayer1Turn(){
    player1Turn = true;
}


void Game::moveFigurine(int x0, int y0, int x1, int y1){
    board->SetFigure(board->GetFigure(x0, y1), x1, y1);
    board->SetFigure(0, x0, y0);
}



void Game::jumpFigurine(int x0, int y0, int x1, int y1){
    moveFigurine(x0, y0, x1, y1);

    Vector2D enemyPosition = calculateEnemyPosition(x0, y0, x1, y1);
    board->SetFigure(0, enemyPosition.x, enemyPosition.y);
}



void Game::resolveKingMove(const vector<int>& capturedFigurines, int x0, int y0, int x1, int y1){

}

void Game::tryToCrownFigurine(int x0, int y0){

}

void Game::endTurn(){

}

bool Game::ResolveMove(const string& message){

    int xStart = message[0] - '0';
    int yStart = message[2] - '0';

    int xEnd = message[4] - '0';
    int yEnd = message[6] - '0';

    int figurine = board->GetFigure(xStart, yStart);
    if (!board->IsFigurine(figurine))
        return false;


    int figurineInWay = board->GetFigure(xEnd, yEnd);
    if (!board->IsFigurine(figurineInWay))
        return false;

    if (!Utils::IsDiagonal(xStart, yStart, xEnd, yEnd))
        return false;

    if (Utils::CanBeValidWalk(xStart, yStart, xEnd, yEnd))
    {
        moveFigurine(xStart, yStart, xEnd, yEnd);
        endTurn();
    }
    else if (Utils::CanBeValidJump(board, xStart, yStart, xEnd, yEnd))
    {
        jumpFigurine(xStart, yStart, xEnd, yEnd);
    }
    else if (board->IsKing(figurine))
    {
        vector<int> capturedFigurines;

        bool isValidMove = Utils::ValidateKingMove(capturedFigurines, xStart, yStart, xEnd, yEnd);
        if (isValidMove)
        {
            resolveKingMove(capturedFigurines, xStart, yStart, xEnd, yEnd);
        }
    }

    tryToCrownFigurine(xStart, yStart);
}