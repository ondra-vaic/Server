//
// Created by me on 11/5/19.
//


#include <vector>
#include <cmath>
#include <tuple>

#include "Game.h"
#include "Vector2D.h"
#include "Utils.h"
#include "NetworkManager.h"

using namespace std;

Game::Game(int player1, int player2, Board* board) :
player1(player1), player2(player2), board(board),
pickedField(Vector2D{-1, -1}), player1Turn(true), hasMoved(false), turnEnded(false){}

int Game::GetCurrentPlayer() {
    return player1Turn ? player1 : player2;
}

int Game::getOtherPlayer() {
    return player1Turn ?  player2 : player1;
}

void Game::EndTurn(){
    turnEnded = true;
}

bool Game::isPickedField(int x, int y){return x == pickedField.x && y == pickedField.y;}

void Game::setPickedField(int x, int y){
    pickedField.x = x;
    pickedField.y = y;
}

void Game::moveFigurine(int x0, int y0, int x1, int y1){
    board->SetFigure(board->GetFigurine(x0, y0), x1, y1);
    board->SetFigure(0, x0, y0);
    NetworkManager::SendMove(getOtherPlayer(), x0, y0, x1, y1);
    tryToCrownFigurine(x1, y1);
}

void Game::deleteFigurine(int x, int y){
    board->SetFigure(0, x, y);
    NetworkManager::SendDelete(getOtherPlayer(), x, y);
}

void Game::jumpFigurine(int x0, int y0, int x1, int y1){
    moveFigurine(x0, y0, x1, y1);

    Vector2D enemyPosition = Utils::CalculateEnemyPosition(x0, y0, x1, y1);
    deleteFigurine(enemyPosition.x, enemyPosition.y);
    setPickedField(x1, y1);
    hasMoved = true;
}

void Game::resolveKingMove(const vector<Vector2D>& capturedFigurines, int x0, int y0, int x1, int y1){

    moveFigurine(x0, y0, x1, y1);

    for (Vector2D capturedFigurine : capturedFigurines) {
        deleteFigurine(capturedFigurine.x, capturedFigurine.y);
    }

    if (!capturedFigurines.empty())
    {
        hasMoved = true;
    }
    else
    {
        endTurn();
    }

    setPickedField(x1, y1);
}

void Game::tryToCrownFigurine(int x, int y){
    if(y == 7)
    {
        board->SetFigure(2, x, y);
        NetworkManager::SendCrown(getOtherPlayer(), x, y);
    }
}

void Game::endTurn(){
    turnEnded = true;
    cout << "turn ended for " << GetCurrentPlayer() << endl;
}

void Game::Switch(){
    NetworkManager::SendWake(getOtherPlayer());
    player1Turn = !player1Turn;
    hasMoved = false;
    turnEnded = false;
    board->FlipBoard();
}

bool Game::HasTurnEnded(){return turnEnded;}

bool Game::ResolvePick(const string& message) {

    int x = message[0] - '0';
    int y = message[2] - '0';

    int figurine = board->GetFigurine(x, y);

    if (!Utils::IsFigurine(figurine))
        return false;

    if (!hasMoved)
    {
        if (Utils::IsPlayer1(figurine))
        {
            setPickedField(x, y);
        }
    }
    else if(isPickedField(x, y)){
        endTurn();
    }

    cout << "picked" << endl;

    return true;
}

bool Game::ResolveMove(const string& message){
    
    int xStart = message[0] - '0';
    int yStart = message[2] - '0';

    int xEnd = message[4] - '0';
    int yEnd = message[6] - '0';

    int figurine = board->GetFigurine(xStart, yStart);
    int figurineInWay = board->GetFigurine(xEnd, yEnd);

    if(!isPickedField(xStart, yStart))
        return false;

    cout << "is picked field" << endl;
    cout << "figurine is " << figurine << endl;

    if (!Utils::IsFigurine(figurine))
        return false;

    cout << "there is figurine on picked field" << endl;

    if (!Utils::IsEmptyField(figurineInWay))
        return false;

    cout << "target field is empty field" << endl;

    if (!Utils::IsDiagonal(xStart, yStart, xEnd, yEnd))
        return false;

    cout << "the move is diagonal" << endl;

    if (Utils::CanBeValidWalk(xStart, yStart, xEnd, yEnd))
    {
        moveFigurine(xStart, yStart, xEnd, yEnd);
        endTurn();
        cout << "moved" << endl;
    }
    else if (Utils::CanBeValidJump(board, xStart, yStart, xEnd, yEnd))
    {
        jumpFigurine(xStart, yStart, xEnd, yEnd);
        cout << "jump" << endl;
    }
    else if (Utils::IsKing(figurine))
    {
        vector<Vector2D> capturedFigurines;

        bool isValidMove = Utils::ValidateKingMove(capturedFigurines, board, xStart, yStart, xEnd, yEnd);
        if (isValidMove)
        {
            cout << "king move" << endl;
            resolveKingMove(capturedFigurines, xStart, yStart, xEnd, yEnd);
        }
    }


    return true;
}