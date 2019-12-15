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
class Room : public IMessageHandler{

private:
    vector<Player*> playersToLeave;
    vector<PlayerInRoom*> playersInRoom;
    vector<Session*> sessions;
    void resolvePlayersInRoom(fd_set* sockets);
    void resolveSessions(fd_set* sockets);

public:
    void ResolveMessage(fd_set* sockets) override;
    vector<Player*> GetPlayers();
    void SetPlayer(Player* player);
    void CreateSessions();
    void SendPeriodicMessages();
    vector<Player*> GetPlayersToLeave();
    vector<Player*> GetPlayersToJoinGame();
    vector<Player*> GetWaitingPlayers();
    vector<Player*> GetPlayersInSessions();

};


#endif //SERVER_ROOM_H
