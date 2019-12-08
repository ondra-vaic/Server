//
// Created by me on 12/7/19.
//

#ifndef SERVER_PLAYERINROOM_H
#define SERVER_PLAYERINROOM_H


#include "IMessageHandler.h"
#include "../Player.h"

class PlayerInRoom : public IMessageHandler{

public:
    enum State{WANTS_TO_JOIN, WANTS_TO_LEAVE, CHILLING, JOINING_GAME, EXITED_GAME};
    explicit PlayerInRoom(Player* player);
    void ResolveMessage(fd_set* sockets) override;
    bool WantsToLeave();
    bool WantsToJoinGame();
    bool IsJoiningGame();
    bool ExitedGame();
    void SetJoiningGame();
    Player* GetPlayer();


private:
    Player* player;
    State state;
    bool chilling(Message* message);
    bool waitingForGame(Message* message);

};


#endif //SERVER_PLAYERINROOM_H
