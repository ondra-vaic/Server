//
// Created by me on 12/8/19.
//

#ifndef SERVER_PLAYERINGAME_H
#define SERVER_PLAYERINGAME_H


#include "IMessageHandler.h"
#include "../Game.h"
#include "LeafHandler.h"

enum PlayerInGameState{PLAYING, WAITING, WON, LOST};

class PlayerInGame : public LeafHandler<PlayerInGameState, PlayerInGame>{

public:
    explicit PlayerInGame(PlayerPtr player, GamePtr game, PlayerInGameState state);
    void SendPeriodicMessages() override;

private:
    GamePtr game;
    void init() override;

    bool resolvePick(const MessagePtr& message);
    bool resolveMove(const MessagePtr& message);
    bool endTurn(const MessagePtr& message);
    bool setForfeited(const MessagePtr& message);
    bool forfeitWhileWaiting(const MessagePtr& message);

};

typedef shared_ptr<PlayerInGame> PlayerInGamePtr;

#endif //SERVER_PLAYERINGAME_H
