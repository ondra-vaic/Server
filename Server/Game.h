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
    bool turnEnded;
    Vector2D pickedField;
    Board* board;


    void moveFigurine(int x0, int y0, int x1, int y1);
    void jumpFigurine(int x0, int y0, int x1, int y1);
    void resolveKingMove(const vector<Vector2D>& capturedFigurines, int x0, int y0, int x1, int y1);
    void tryToCrownFigurine(int x0, int y0);
    void endTurn();
    bool isPickedField(int x, int y);
    void setPickedField(int x, int y);
    void deleteFigurine(int x, int y);

public:
    Game(int player1, int player2, Board* board);
    int GetCurrentPlayer();
    int getOtherPlayer();
    bool ResolveMove(const string& message);
    bool ResolvePick(const string& message);
    bool HasTurnEnded();
    void EndTurn();
    void Switch();
};


#endif //SERVER_GAME_H
