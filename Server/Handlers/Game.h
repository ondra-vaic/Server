//
// Created by me on 11/5/19.
//

#ifndef SERVER_GAME_H
#define SERVER_GAME_H


#include "../Board.h"
#include "../Vector2D.h"
#include "../Message.h"
#include "../Player.h"
#include "IMessageHandler.h"
#include <vector>


class Game {

private:
    Player* player1;
    Player* player2;
    int messageNumber;
    bool player1Turn;
    bool hasMoved;
    bool turnEnded;
    bool forfeited;
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
    Game(Player* player1, Player* player2);
    Player* GetCurrentPlayer();
    Player* GetOtherPlayer();
    int GetCurrentMessageNumber();
    bool ResolveMove(const string& message);
    bool ResolvePick(const string& message);
    bool HasTurnEnded();
    bool IsJustWon();
    bool CanMove();
    void EndTurn();
    void Switch();
    void SetForfeited();
    bool HasForfeited();

};


#endif //SERVER_GAME_H
