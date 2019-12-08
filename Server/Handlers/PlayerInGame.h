//
// Created by me on 12/8/19.
//

#ifndef SERVER_PLAYERINGAME_H
#define SERVER_PLAYERINGAME_H


#include "IMessageHandler.h"
#include "Game.h"

class PlayerInGame : public IMessageHandler{

public:
    PlayerInGame(Player* player, Game* game);
    void ResolveMessage() override;

private:


};


#endif //SERVER_PLAYERINGAME_H
