//
// Created by me on 12/6/19.
//

#ifndef SERVER_ROOM_H
#define SERVER_ROOM_H

#include <vector>
#include "IMessageHandler.h"
#include "../Player.h"
#include "Session.h"
#include "PlayerInRoom.h"
#include "PlayerSetup.h"

class Room : public IMessageHandler{

private:
    vector<PlayerSetup*> playersToLeave;
    vector<PlayerInRoom*> playersInRoom;
    vector<Session*> sessions;
    void resolvePlayersInRoom(fd_set* sockets);
    void resolveSessions(fd_set* sockets);

public:
    void ResolveMessage(fd_set* sockets) override;
    int NumPlayers();
    vector<int> GetPlayers();
    void PassMessages();
    void SetPlayer(Player* player);
    void CreateSessions();
    vector<PlayerSetup*> GetPlayersToLeave();

};


#endif //SERVER_ROOM_H
