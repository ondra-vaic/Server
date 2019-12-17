//
// Created by me on 12/5/19.
//

#ifndef SERVER_SESSION_H
#define SERVER_SESSION_H


#include "../Game.h"
#include "../Player.h"
#include "PlayerInGame.h"


class Session : public IMessageHandler{

public:
    enum State{SESSION_ON, SESSION_ENDED};
    Session(const PlayerPtr& player1, const PlayerPtr& player2);
    PlayerInGamePtr GetPlayer1();
    PlayerInGamePtr GetPlayer2();
    void SendPeriodicMessages() override;
    bool IsEnded();
    void ResolveMessage(fd_set* sockets) override;

private:
    State state;
    GamePtr game;
    PlayerInGamePtr player1;
    PlayerInGamePtr player2;
    void resolveCheaterLeaver(const PlayerPtr& player);
};

typedef shared_ptr<Session> SessionPtr;

#endif //SERVER_SESSION_H
