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
    explicit PlayerSetup(Player* player, vector<Room*>& rooms, unordered_set<string>& usedNames, PlayerSetupState state);
    bool IsPlayerInitialized();
    bool IsPlayerToLeave();
    void SendPeriodicMessages() override;

private:
    vector<Room*> rooms;
    unordered_set<string> usedNames;

    bool setName(Message* message);
    bool setRoom(Message* message);

    bool exitGame(Message* message);
    bool backToChoosingName(Message* message);

    bool nameIsUsed(const string& proposedName);
    void sendRoomsInfo();
    void init() override;
};


#endif //SERVER_PLAYERSETUP_H
