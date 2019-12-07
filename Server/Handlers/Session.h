//
// Created by me on 12/5/19.
//

#ifndef SERVER_SESSION_H
#define SERVER_SESSION_H


#include "Game.h"
#include "Lobby.h"
#include "Disconnect.h"
#include "IMessageHandler.cpp"

class Session : public IMessageHandler{

public:
    Session(int player1);
    bool ResolveNextMessage(int player);
    int GetPlayer1();
    int GetPlayer2();
    void SetPlayer2(int player2);
    void SetPlayer1(int player1);

private:
    IMessageHandler* handler;
    State state;
    int player1;
    int player2;
};


#endif //SERVER_SESSION_H
