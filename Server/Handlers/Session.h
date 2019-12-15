//
// Created by me on 12/5/19.
//

#ifndef SERVER_SESSION_H
#define SERVER_SESSION_H


#include "Game.h"
#include "Disconnect.h"
#include "../Player.h"
#include "PlayerInGame.h"


class Session : public IMessageHandler{

public:
    enum State{SESSION_ON, SESSION_ENDED};
    Session(Player* player1, Player* player2);
    PlayerInGame* GetPlayer1();
    PlayerInGame* GetPlayer2();
    void SendPeriodicMessages() override;

    void ResolveMessage(fd_set* sockets);
    bool IsEnded();

private:
    State state;
    Game* game;
    PlayerInGame* player1;
    PlayerInGame* player2;
    void resolveCheaterLeaver(Player* player);
};


#endif //SERVER_SESSION_H
