//
// Created by me on 12/7/19.
//

#include <utility>
#include <vector>
#include <array>
#include "PlayerSetup.h"
#include "../NetworkManager.h"
#include "../Identifiers.h"
#include <functional>

class Room;

PlayerSetup::PlayerSetup(const PlayerPtr& player, vector<RoomPtr>& rooms, unordered_set<string>& usedNames, PlayerSetupState state)
: LeafHandler<PlayerSetupState, PlayerSetup>(player){
    this->state = state;
    this->usedNames = usedNames;
    this->rooms = rooms;
    this->reconnected = false;

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
    commands[SETTING_NAME][TRY_RECONNECT] = bind(&PlayerSetup::tryReconnect, this, _1);

    commands[CHOOSING_ROOM][ROOM_ENTER] = bind(&PlayerSetup::setRoom, this, _1);
    commands[CHOOSING_ROOM][BACK] = bind(&PlayerSetup::backToChoosingName, this, _1);
}

bool PlayerSetup::exitGame(const MessagePtr& message){
    state = LEAVE;
    cout << "State set " << endl;
    return message->GetData().empty();
}

bool PlayerSetup::backToChoosingName(const MessagePtr& message){
    NetworkManager::SendConfirmBackFromSetup(player);
    state = SETTING_NAME;
    return message->GetData().empty();
}

bool PlayerSetup::setName(const MessagePtr& message){

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

bool PlayerSetup::HasReconnected(){
    return reconnected;
}

bool PlayerSetup::tryReconnect(const MessagePtr& message){
    string name = message->GetData();
    player->SetName(name);

    for (auto& room : rooms) {
        for(auto& session : room->GetSessions()){
            if(session->TryReconnect(player)){
                NetworkManager::SendIsReconnected(player);
                reconnected = true;
                return true;
            }
        }
    }

    player->SetName("");
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

bool PlayerSetup::setRoom(const MessagePtr& message){
    try {
        int room = stoi(message->GetData());
        if(room >= 0 && room < rooms.size()){
            player->SetRoom(room);
            state = ROOM_CHOSEN;
            NetworkManager::SendConfirmRoom(player);
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
//    bool nameUsed = usedNames.find(proposedName) != usedNames.end();
//    cout << "name is used " << nameUsed <<endl;
    return usedNames.find(proposedName) != usedNames.end();
}


