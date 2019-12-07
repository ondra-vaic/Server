//
// Created by me on 12/6/19.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include "Handlers/IMessageHandler.cpp"
#include "Handlers/Room.h"


class Server : public IMessageHandler{

private:
    struct sockaddr_in serverAddress;
    int maxPlayers;
    int maxSocket;
    int serverSocket;
    int addressLength;
    fd_set sockets;
    vector<Room*> rooms;
    vector<int> playersOutsideRoom;
    int numberOfConnectedPlayers();
    void handleNewPlayer(int newPlayer);
    vector<int> getActiveSockets();
    int setSocketSet();
    void handleNewMessages();

public:
    explicit Server(int maxSessions, int maxPendingConnections, int port, int numberOfRooms);
    void MainLoop();

};


#endif //SERVER_SERVER_H
