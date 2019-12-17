//
// Created by me on 12/7/19.
//

#include "PlayerInRoom.h"

#include <utility>
#include "../NetworkManager.h"
#include "../Identifiers.h"

PlayerInRoom::PlayerInRoom(PlayerPtr player) : LeafHandler<PlayerInRoomState, PlayerInRoom>(move(player)){
    this->state = CHILLING;
}

void PlayerInRoom::init(){
    commands[CHILLING][WAIT_GAME] = bind(&PlayerInRoom::setWantsToJoin, this, _1);
    commands[CHILLING][BACK] = bind(&PlayerInRoom::backToChoosingRoom, this, _1);

    commands[WANTS_TO_JOIN][STOP_WAIT_GAME] = bind(&PlayerInRoom::stopWaitingGame, this, _1);
    commands[WANTS_TO_JOIN][BACK] = bind(&PlayerInRoom::backToChoosingRoom, this, _1);
}

void PlayerInRoom::SendPeriodicMessages(){

}

bool PlayerInRoom::setWantsToJoin(const MessagePtr& message){
    state = WANTS_TO_JOIN;
    return message->GetData().empty();
}

bool PlayerInRoom::stopWaitingGame(const MessagePtr& message){
    state = CHILLING;
    return message->GetData().empty();
}

bool PlayerInRoom::backToChoosingRoom(const MessagePtr& message){
    state = WANTS_TO_LEAVE;
    return message->GetData().empty();
}

void PlayerInRoom::SetJoiningGame(){
    state = JOINING_GAME;
}

bool PlayerInRoom::WantsToJoinGame(){
    return state == WANTS_TO_JOIN;
}

bool PlayerInRoom::WantsToLeave(){
    return state == WANTS_TO_LEAVE;
}


bool PlayerInRoom::IsJoiningGame(){
    return state == JOINING_GAME;
}

void PlayerInRoom::SendRoomInfo(int playersToJoin, int playersInSession, int waitingPlayers){
        array<int, 3> info {playersToJoin,
                            playersInSession,
                            waitingPlayers};
    NetworkManager::SendRoomInfo(player, info);
}
