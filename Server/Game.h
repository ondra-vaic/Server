//
// Created by me on 11/5/19.
//

#ifndef SERVER_GAME_H
#define SERVER_GAME_H


#include "Board.h"
#include "Vector2D.h"
#include "Message.h"
#include "Player.h"
#include <vector>


class Game {

private:
    PlayerPtr player1;
    PlayerPtr player2;
    int messageNumber;
    bool player1Turn;
    bool hasMoved;
    bool turnEnded;
    bool forfeited;
    Vector2D pickedField;
    BoardPtr board;

    void moveFigurine(int x0, int y0, int x1, int y1);
    void jumpFigurine(int x0, int y0, int x1, int y1);
    void resolveKingMove(const vector<Vector2D>& capturedFigurines, int x0, int y0, int x1, int y1);
    void tryToCrownFigurine(int x0, int y0);
    void endTurn();
    bool isPickedField(int x, int y);
    void setPickedField(int x, int y);
    void deleteFigurine(int x, int y);

public:
    Game(const PlayerPtr& player1, const PlayerPtr& player2);
    PlayerPtr GetCurrentPlayer();
    PlayerPtr GetOtherPlayer();
    PlayerPtr GetOtherPlayer(const PlayerPtr& player);
    int GetCurrentMessageNumber();
    bool ResolveMove(const string& message);
    bool ResolvePick(const string& message);
    bool HasTurnEnded();
    bool IsJustWon();
    bool CanMove();
    bool EndTurn(const string& message);
    void Switch();
    bool SetForfeited(const string& message);
    bool HasForfeited();
    BoardPtr GetBoard();

};

typedef shared_ptr<Game> GamePtr;

#endif //SERVER_GAME_H
