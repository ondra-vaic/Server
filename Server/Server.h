//
// Created by me on 12/6/19.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include <netinet/in.h>
#include <bits/stdc++.h>
#include "Handlers/Room.h"
#include "Handlers/PlayerSetup.h"
#include "Game.h"
#include "Game.h"

class Server : public IMessageHandler{

private:
    struct sockaddr_in serverAddress;
    int maxPlayers;
    int maxSocket;
    int serverSocket;
    int addressLength;
    int lastPeriodicMessageTime;
    fd_set sockets;
    vector<RoomPtr> rooms;
    vector<PlayerSetupPtr> playerSetups;
    unordered_set<string> names;

    int numberOfConnectedPlayers();
    void handleNewPlayer(int newPlayer);
    vector<PlayerPtr> getAllPlayers();
    int setSocketSet();
    void resolveSetUps();
    void resolveRooms();

public:
    explicit Server(int maxPlayers, int maxPendingConnections, int port, int numberOfRooms);
    void MainLoop();
    void ResolveMessage(fd_set* sockets) override;
    void SendPeriodicMessages() override;
};


#endif //SERVER_SERVER_H
