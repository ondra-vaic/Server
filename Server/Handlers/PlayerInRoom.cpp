//
// Created by me on 12/7/19.
//

#include <vector>
#include "PlayerInRoom.h"
#include "../NetworkManager.h"
#include "../Identifiers.h"

PlayerInRoom::PlayerInRoom(Player *player) {
    this->player = player;
    this->state = CHILLING;
}

void PlayerInRoom::ResolveMessage(fd_set* sockets){
    if(!FD_ISSET(player->GetSocketId(), sockets)){
        return;
    }

    vector<string> splitMessages = NetworkManager::GetSplitMessages(player);

    if(player->IsDisconnected()){
        return;
    }

    for (const string& message : splitMessages) {
        Message* m = new Message(message, player);

        switch(state){
            case CHILLING:
                chilling(m);
                break;
            case WANTS_TO_JOIN:
                waitingForGame(m);
                break;
            default:
                //TODO ??
                break;
        }
    }
}

bool PlayerInRoom::waitingForGame(Message* message){
    switch (message->GetIdentifier()) {
        case STOP_WAIT_GAME:
            state = CHILLING;
            break;
        case EXIT_GAME:
            state = EXITED_GAME;
            break;
        case LEAVE_ROOM:
            state = WANTS_TO_LEAVE;
        default:
            //TODO ??
            break;
    }
}

bool PlayerInRoom::chilling(Message* message){
    switch (message->GetIdentifier()) {
        case WAIT_GAME:
            state = WANTS_TO_JOIN;
            break;
        case EXIT_GAME:
            state = EXITED_GAME;
            break;
        case LEAVE_ROOM:
            state = WANTS_TO_LEAVE;
            break;
        default:
            //TODO ??
            break;
    }
}

void PlayerInRoom::SetJoiningGame(){
    state = JOINING_GAME;
}

Player* PlayerInRoom::GetPlayer(){
    return player;
}

bool PlayerInRoom::WantsToJoinGame(){
    return state == WANTS_TO_JOIN;
}

bool PlayerInRoom::WantsToLeave(){
    return state == WANTS_TO_LEAVE;
}

bool PlayerInRoom::ExitedGame(){
    return state == EXITED_GAME;
}

bool PlayerInRoom::IsJoiningGame(){
    return state == JOINING_GAME;
}
