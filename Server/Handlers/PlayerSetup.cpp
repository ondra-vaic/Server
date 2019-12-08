//
// Created by me on 12/7/19.
//

#include <vector>
#include "PlayerSetup.h"
#include "../NetworkManager.h"
#include "../Identifiers.h"

PlayerSetup::PlayerSetup(int playerSocket, State state){
    this->state = state;
    player = new Player(playerSocket);
}

PlayerSetup::PlayerSetup(Player* player, State state){
    this->state = state;
    this->player = player;
}

void PlayerSetup::ResolveMessage(fd_set* sockets){
    if(!FD_ISSET(player->GetSocketId(), sockets)){
        return;
    }

    bool disconnected = false;
    vector<string> splitMessages = NetworkManager::GetSplitMessages(player->GetSocketId(), &disconnected);

    if(disconnected){
        //TODO ????
    }

    for (const string& message : splitMessages) {
        Message* m = new Message(message);

        switch(state){
            case SETTING_NAME:
                settingName(m);
                break;
            case CHOOSING_ROOM:
                settingRoom(m);
                break;
            case ROOM_CHOSEN:
                //TODO
                break;
            default:
                //TODO ??
                break;
        }

    }
}

bool PlayerSetup::settingName(Message* message){
    switch (message->GetIdentifier()) {
        case NAME_IDENTIFY:
            setName(message);
            break;
        case EXIT_GAME:
            state = LEAVE;
            break;
        default:
            //TODO ??
            break;
    }
}

bool PlayerSetup::settingRoom(Message* message){
    switch (message->GetIdentifier()) {
        case ROOM_ENTER:
            setRoom(message);
            break;
        case EXIT_GAME:
            state = LEAVE;
            break;
        default:
            //TODO ??
            break;
    }
}

bool PlayerSetup::setName(Message* message){

    state = CHOOSING_ROOM;
}

bool PlayerSetup::setRoom(Message* message){

}

bool PlayerSetup::IsPlayerInitialized(){
    return state == ROOM_CHOSEN;
}

bool PlayerSetup::IsPlayerToLeave(){
    return state == LEAVE;
}

Player* PlayerSetup::GetPlayer(){
    return player;
}