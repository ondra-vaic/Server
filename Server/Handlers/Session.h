//
// Created by me on 12/5/19.
//

#ifndef SERVER_SESSION_H
#define SERVER_SESSION_H


#include "Game.h"
#include "Lobby.h"
#include "Disconnect.h"
#include "IMessageHandler.h"
#include "../Player.h"
#include "PlayerInGame.h"


class Session : public IMessageHandler{

public:
    enum State{SESSION_ENDED};
    Session(Player* player1, Player* player2);
    Player* GetPlayer1();
    Player* GetPlayer2();
    void ResolveMessage(fd_set* sockets);
    bool IsEnded();

private:
    State state;
    PlayerInGame* player1;
    PlayerInGame* player2;
};


#endif //SERVER_SESSION_H
