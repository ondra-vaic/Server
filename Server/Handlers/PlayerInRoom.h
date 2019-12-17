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
typedef shared_ptr<Room> RoomPtr;

enum PlayerInRoomState{WANTS_TO_JOIN, WANTS_TO_LEAVE, CHILLING, JOINING_GAME};

class PlayerInRoom : public LeafHandler<PlayerInRoomState, PlayerInRoom>{

public:

    explicit PlayerInRoom(PlayerPtr player);

    bool WantsToLeave();
    bool WantsToJoinGame();
    bool IsJoiningGame();
    void SetJoiningGame();
    void SendRoomInfo(int playersToJoin, int playersInSession, int waitingPlayers);
    void SendPeriodicMessages() override;

private:
    RoomPtr room;
    bool setWantsToJoin(const MessagePtr& message);
    bool stopWaitingGame(const MessagePtr& message);
    bool backToChoosingRoom(const MessagePtr& message);

    void init() override;

};

typedef shared_ptr<PlayerInRoom> PlayerInRoomPtr;

#endif //SERVER_PLAYERINROOM_H
