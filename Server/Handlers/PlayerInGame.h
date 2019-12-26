//
// Created by me on 12/8/19.
//

#ifndef SERVER_PLAYERINGAME_H
#define SERVER_PLAYERINGAME_H


#include "IMessageHandler.h"
#include "../Game.h"
#include "LeafHandler.h"

enum PlayerInGameState{PLAYING, WAITING, FORFEITED, DISCONNECTED, WAITING_RECONNECT};

typedef shared_ptr<Game> GamePtr;
class PlayerInGame : public LeafHandler<PlayerInGameState, PlayerInGame>{

public:
    explicit PlayerInGame(const PlayerPtr& player, const GamePtr& game, PlayerInGameState state);
    void SetStateBeforeDc();
    void SetWaitingForReconnect();
    void SetDced();
    void ResetState();
    void SetWaiting();
    void SetPlaying();
    bool IsPlaying();
    bool IsWaiting();
    bool HasForfeited();

private:
    GamePtr game;
    PlayerInGameState stateBeforeDc;

    void init() override;
    bool resolvePick(const MessagePtr& message);
    bool resolveMove(const MessagePtr& message);
    bool endTurn(const MessagePtr& message);
    bool setForfeited(const MessagePtr& message);
    bool sendInfo(const MessagePtr& message);
};

typedef shared_ptr<PlayerInGame> PlayerInGamePtr;

#endif //SERVER_PLAYERINGAME_H
