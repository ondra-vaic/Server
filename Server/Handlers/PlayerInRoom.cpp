//
// Created by me on 12/7/19.
//

#include <vector>
#include "PlayerInRoom.h"
#include "../NetworkManager.h"
#include "../Identifiers.h"

PlayerInRoom::PlayerInRoom(Player* player, Room* room) : LeafHandler<PlayerInRoomState, PlayerInRoom>(player){
    this->room = room;
    this->state = CHILLING;
}

void PlayerInRoom::SendPeriodicMessages(){
    sendRoomInfo();
}

void PlayerInRoom::init(){
    commands[CHILLING][WAIT_GAME] = bind(&PlayerInRoom::setWantsToJoin, this, _1);
    commands[CHILLING][BACK] = bind(&PlayerInRoom::backToChoosingRoom, this, _1);

    commands[WANTS_TO_JOIN][STOP_WAIT_GAME] = bind(&PlayerInRoom::stopWaitingGame, this, _1);
    commands[WANTS_TO_JOIN][BACK] = bind(&PlayerInRoom::backToChoosingRoom, this, _1);
}

bool PlayerInRoom::setWantsToJoin(Message* message){
    state = WANTS_TO_JOIN;
    return message->GetData().empty();
}

bool PlayerInRoom::stopWaitingGame(Message* message){
    state = CHILLING;
    return message->GetData().empty();
}

bool PlayerInRoom::backToChoosingRoom(Message* message){
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

void PlayerInRoom::sendRoomInfo(){
        array<int, 3> info {(int)room->GetPlayersToJoinGame().size(),
                            (int)room->GetPlayersInSessions().size(),
                            (int)room->GetWaitingPlayers().size()};
    NetworkManager::SendRoomInfo(player, info);
}
