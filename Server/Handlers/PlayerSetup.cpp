//
// Created by me on 12/7/19.
//

#include <vector>
#include "PlayerSetup.h"
#include "../NetworkManager.h"
#include "../Identifiers.h"

class Room;

PlayerSetup::PlayerSetup(int playerSocket, vector<Room*>& rooms, unordered_set<string>& usedNames, State state){
    this->state = state;
    this->usedNames = usedNames;
    this->rooms = rooms;
    player = new Player(playerSocket);
}

PlayerSetup::PlayerSetup(Player *player, State state) {
    this->state = state;
    this->player = player;
}

void PlayerSetup::ResolveMessage(fd_set* sockets){

    cout << "Resolving setup message" << endl;

    if(!FD_ISSET(player->GetSocketId(), sockets)){
        return;
    }

    vector<string> splitMessages = NetworkManager::GetSplitMessages(player);

    if(player->IsDisconnected()){
        return;
    }

    for (const string& message : splitMessages) {
        Message* m = new Message(message, player);

        if(player->IsCheating() || player->IsDisconnected())
            return;

        switch(state){
            case SETTING_NAME:
                settingName(m);
                continue;
            case CHOOSING_ROOM:
                settingRoom(m);
                continue;
            case ROOM_CHOSEN:
                //TODO
                continue;
            default:
                //TODO ??
                continue;
        }
    }
}

bool PlayerSetup::settingName(Message* message){
    switch (message->GetIdentifier()) {
        case NAME_IDENTIFY:
            if(!setName(message)){
                player->SetCheating();
            }
            break;
        case EXIT_GAME:
            state = LEAVE;
            break;
        default:
            player->SetCheating();
            break;
    }

    return true;
}

bool PlayerSetup::settingRoom(Message* message){
    switch (message->GetIdentifier()) {
        case ROOM_ENTER:
            if(!setRoom(message)){
                player->SetCheating();
            }
            break;
        case EXIT_GAME:
            state = LEAVE;
            break;
        default:
            player->SetCheating();
            break;
    }

    return true;
}

bool PlayerSetup::setName(Message* message){

    string proposedName = message->GetData();

    for (auto& name : usedNames) {
        cout << name <<endl;
    }

    if (!nameIsUsed(proposedName))
    {
        usedNames.insert(proposedName);
        player->SetName(proposedName);
        state = CHOOSING_ROOM;
        NetworkManager::SendConfirmName(player);
    }else{
        NetworkManager::SendDenyName(player);
    }

    return true;
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

Player* PlayerSetup::GetPlayer(){
    return player;
}