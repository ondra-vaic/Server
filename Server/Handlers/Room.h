//
// Created by me on 12/6/19.
//

#ifndef SERVER_ROOM_H
#define SERVER_ROOM_H

#include <vector>
#include "../Player.h"
#include "Session.h"
#include "PlayerInRoom.h"

class PlayerInRoom;
typedef shared_ptr<PlayerInRoom> PlayerInRoomPtr;

class Room : public IMessageHandler{

private:
    vector<PlayerPtr> playersToLeave;
    vector<PlayerInRoomPtr> playersInRoom;
    vector<SessionPtr> sessions;
    void resolvePlayersInRoom(fd_set* sockets);
    void resolveSessions(fd_set* sockets);

public:
    void ResolveMessage(fd_set* sockets) override;
    vector<PlayerPtr> GetPlayers();
    void SetPlayer(const PlayerPtr& player);
    void createSessions();
    void SendPeriodicMessages();
    vector<PlayerPtr> GetPlayersToLeave();
    vector<PlayerPtr> GetPlayersToJoinGame();
    vector<PlayerPtr> GetWaitingPlayers();
    vector<PlayerPtr> GetPlayersInSessions();

};

typedef shared_ptr<Room> RoomPtr;


#endif //SERVER_ROOM_H
