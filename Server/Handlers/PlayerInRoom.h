//
// Created by me on 12/7/19.
//

#ifndef SERVER_PLAYERINROOM_H
#define SERVER_PLAYERINROOM_H


#include "../Player.h"
#include "IMessageHandler.h"
#include "LeafHandler.h"
#include "../Message.h"
#include "Room.h"

class Room;
enum PlayerInRoomState{WANTS_TO_JOIN, WANTS_TO_LEAVE, CHILLING, JOINING_GAME};

class PlayerInRoom : public LeafHandler<PlayerInRoomState, PlayerInRoom>{

public:

    explicit PlayerInRoom(Player* player, Room* room);

    bool WantsToLeave();
    bool WantsToJoinGame();
    bool IsJoiningGame();
    void SetJoiningGame();
    void SendPeriodicMessages() override;

private:
    Room* room;
    bool setWantsToJoin(Message* message);
    bool stopWaitingGame(Message* message);
    bool backToChoosingRoom(Message* message);
    void sendRoomInfo();

    void init() override;

};


#endif //SERVER_PLAYERINROOM_H
