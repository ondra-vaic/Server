//
// Created by me on 12/7/19.
//

#include <vector>
#include <array>
#include "PlayerSetup.h"
#include "../NetworkManager.h"
#include "../Identifiers.h"
#include <functional>

class Room;

PlayerSetup::PlayerSetup(Player* player, vector<Room*>& rooms, unordered_set<string>& usedNames, PlayerSetupState state)
: LeafHandler<PlayerSetupState, PlayerSetup>(player){
    this->state = state;
    this->usedNames = usedNames;
    this->rooms = rooms;

    if(state == CHOOSING_ROOM)
        sendRoomsInfo();
}

void PlayerSetup::SendPeriodicMessages(){
    if(state == CHOOSING_ROOM)
        sendRoomsInfo();
}

void PlayerSetup::init(){
    commands[SETTING_NAME][NAME_IDENTIFY] = bind(&PlayerSetup::setName, this, _1);
    commands[SETTING_NAME][EXIT_GAME] = bind(&PlayerSetup::exitGame, this, _1);

    commands[CHOOSING_ROOM][ROOM_ENTER] = bind(&PlayerSetup::setRoom, this, _1);
    commands[CHOOSING_ROOM][BACK] = bind(&PlayerSetup::backToChoosingName, this, _1);
}

bool PlayerSetup::exitGame(Message* message){
    state = LEAVE;
    return message->GetData().empty();
}

bool PlayerSetup::backToChoosingName(Message* message){
    state = SETTING_NAME;
    return message->GetData().empty();
}

bool PlayerSetup::setName(Message* message){

    string proposedName = message->GetData();

    if (!nameIsUsed(proposedName) || proposedName == player->GetName())
    {
        usedNames.insert(proposedName);
        player->SetName(proposedName);
        state = CHOOSING_ROOM;
        NetworkManager::SendConfirmName(player);
        sendRoomsInfo();
    }else{
        NetworkManager::SendDenyName(player);
    }

    return true;
}

void PlayerSetup::sendRoomsInfo(){
    vector<array<int, 3>> roomInfo;
    for (auto& room : rooms) {
        array<int, 3> info {(int)room->GetPlayersToJoinGame().size(),
                            (int)room->GetPlayersInSessions().size(),
                            (int)room->GetWaitingPlayers().size()};
        roomInfo.push_back(info);
    }
    NetworkManager::SendRoomsInfo(player, roomInfo);
}

bool PlayerSetup::setRoom(Message* message){
    try {
        int room = stoi(message->GetData());
        if(room >= 0 && room < rooms.size()){
            player->SetRoom(room);
            state = ROOM_CHOSEN;
            return true;
        }
    }catch ( ... ){
        return false;
    }
    return false;
}

bool PlayerSetup::IsPlayerInitialized(){
    return state == ROOM_CHOSEN;
}

bool PlayerSetup::IsPlayerToLeave(){
    return state == LEAVE;
}

bool PlayerSetup::nameIsUsed(const string& proposedName){
    return usedNames.find(proposedName) != usedNames.end();
}


