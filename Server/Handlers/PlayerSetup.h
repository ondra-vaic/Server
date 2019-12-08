//
// Created by me on 12/7/19.
//

#ifndef SERVER_PLAYERSETUP_H
#define SERVER_PLAYERSETUP_H


#include "IMessageHandler.h"
#include "../Player.h"

class PlayerSetup : public IMessageHandler{

public:
    enum State{SETTING_NAME, CHOOSING_ROOM, ROOM_CHOSEN, LEAVE};
    explicit PlayerSetup(int player, State state);
    explicit PlayerSetup(Player* player, State state);

    void ResolveMessage(fd_set* sockets) override;
    Player* GetPlayer();
    bool IsPlayerInitialized();
    bool IsPlayerToLeave();

private:
    Player* player;
    bool setName(Message* message);
    bool setRoom(Message* message);
    bool settingName(Message* message);
    bool settingRoom(Message* message);
    State state;
};


#endif //SERVER_PLAYERSETUP_H
