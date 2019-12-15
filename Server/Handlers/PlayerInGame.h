//
// Created by me on 12/8/19.
//

#ifndef SERVER_PLAYERINGAME_H
#define SERVER_PLAYERINGAME_H


#include "IMessageHandler.h"
#include "Game.h"

class PlayerInGame : public IMessageHandler{

public:
    enum State{PLAYING, WAITING, WON, LOST};
    PlayerInGame(Player* player, Game* game, State state);
    void ResolveMessage(fd_set* sockets) override;
    void SendPeriodicMessages() override;
    Player* GetPlayer();

private:
    Player* player;
    Game* game;
    State state;
    void playing(Message* message);
    void waiting(Message* message);
    void forfeitWhileWaiting();
};


#endif //SERVER_PLAYERINGAME_H
