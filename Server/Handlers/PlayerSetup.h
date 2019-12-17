//
// Created by me on 12/7/19.
//

#ifndef SERVER_PLAYERSETUP_H
#define SERVER_PLAYERSETUP_H


#include "IMessageHandler.h"
#include "../Player.h"
#include "../Message.h"
#include "Room.h"
#include "LeafHandler.h"
#include <bits/stdc++.h>

enum PlayerSetupState{SETTING_NAME, CHOOSING_ROOM, ROOM_CHOSEN, LEAVE};

class PlayerSetup : public LeafHandler<PlayerSetupState, PlayerSetup>{

public:
    explicit PlayerSetup(PlayerPtr player, vector<RoomPtr>& rooms, unordered_set<string>& usedNames, PlayerSetupState state);
    bool IsPlayerInitialized();
    bool IsPlayerToLeave();
    void SendPeriodicMessages() override;

private:
    vector<RoomPtr> rooms;
    unordered_set<string> usedNames;

    bool setName(const MessagePtr& message);
    bool setRoom(const MessagePtr& message);

    bool exitGame(const MessagePtr& message);
    bool backToChoosingName(const MessagePtr& message);

    bool nameIsUsed(const string& proposedName);
    void sendRoomsInfo();
    void init() override;
};

typedef shared_ptr<PlayerSetup> PlayerSetupPtr;

#endif //SERVER_PLAYERSETUP_H
