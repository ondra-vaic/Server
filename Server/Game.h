//
// Created by me on 11/5/19.
//

#ifndef SERVER_GAME_H
#define SERVER_GAME_H


#include "Board.h"
#include "Vector2D.h"

class Game {

private:
    int player1;
    int player2;
    bool player1Turn;
    bool hasMoved;
    Board* board;
    void moveFigurine(int x0, int y0, int x1, int y1);
    void jumpFigurine(int x0, int y0, int x1, int y1);
    void resolveKingMove(const vector<int>& capturedFigurines, int x0, int y0, int x1, int y1);
    void tryToCrownFigurine(int x0, int y0);
    void endTurn();

public:
    Game(int player1, int player2, Board* board);
    int GetCurrentPlayer();
    int GetOtherPlayer();
    void SetPlayer1Turn();
    bool ResolveMove(const string& message);
    Vector2D calculateEnemyPosition(int x0, int y0, int x1, int y1);

};


#endif //SERVER_GAME_H
