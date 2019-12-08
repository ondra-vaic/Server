//
// Created by me on 12/6/19.
//

#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Handlers/Game.h"
#include "Board.h"
#include "NetworkManager.h"
#include "Handlers/Session.h"
#include "Utils.h"
#include "Server.h"


int Server::numberOfConnectedPlayers(){
    int count = playerSetups.size();
    for (auto & room : rooms) {
        count += room->NumPlayers();
    }
    return count;
}

int Server::setSocketSet(){
    int maxSocket = -1;
    for (int socket : getActiveSockets()) {
        FD_SET(socket, &sockets);
        maxSocket = max(socket, maxSocket);
    }

    return maxSocket;
}

void Server::handleNewPlayer(int newPlayer){

    if(newPlayer < 0){
        Utils::Error(-1, "Failed to accept connection");
    }

    cout << "Accepting new.." << endl;

    if(numberOfConnectedPlayers() < maxPlayers){
        playerSetups.push_back(new PlayerSetup(newPlayer, PlayerSetup::SETTING_NAME));
    }
    else{
        //Send msg and kick
        //TODO kick
    }
}

void Server::resolveSetUps(){
    for(auto& playerSetUp : playerSetups){
        playerSetUp->ResolveMessage(&sockets);

        //add player to room
        if(playerSetUp->IsPlayerInitialized()){
            Player* player = playerSetUp->GetPlayer();
            rooms[player->GetRoom()]->SetPlayer(player);
        }

        if(playerSetUp->IsPlayerToLeave()){
            close(playerSetUp->GetPlayer()->GetSocketId());
        }
    }

    //remove added players from setups
    Utils::RemoveIf(playerSetups,[](PlayerSetup* p){
        return p->IsPlayerInitialized() || p->IsPlayerToLeave();
    });
}

void Server::resolveRooms(){
    for (auto& room : rooms)
    {
        room->ResolveMessage(&sockets);
        room->CreateSessions();
        playerSetups.insert(playerSetups.end(), room->GetPlayersToLeave().begin(), room->GetPlayersToLeave().end());
    }
}

void Server::handleNewMessages(){
    cout << "Receiving messages.." << endl;

    resolveSetUps();
    resolveRooms();
}


Server::Server(int maxClients, int maxPendingConnections, int port, int numberOfRooms){

    this->maxPlayers = maxClients;
    this->maxSocket = 0;

    int param = 1;
    int errorValue;

    //socket
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    errorValue = setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (const char *) &param, sizeof(int));
    Utils::Error(errorValue, "Setsockopt Error");

    //server adress
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    addressLength = sizeof(serverAddress);

    //bind socket
    errorValue = bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    Utils::Error(errorValue, "Bind Error");

    //listen
    errorValue = listen(serverSocket, maxPendingConnections);
    Utils::Error(errorValue, "Listen Error");

    std::cout << "Server up" << std::endl;


    for (int i = 0; i < numberOfRooms; ++i) {
        rooms.push_back(new Room());
    }
}

void Server::MainLoop(){

    while (true) {
        //clear the socket set
        FD_ZERO(&sockets);

        //add master socket to set
        FD_SET(serverSocket, &sockets);

        int maxClientSocket = setSocketSet();
        maxSocket = max(serverSocket, maxClientSocket);

        cout << "Waiting for activity.." <<  " max is " << maxSocket << endl;

        //wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
        int activity = select(maxSocket + 1, &sockets, nullptr, nullptr, nullptr);

        cout << "Resolving Activity.." << endl;
        if (errno != EINTR) {
            if(activity < 0){
                Utils::Error(-1, "select error");
            }
        }

        //If something happened on the master socket , then its an incoming connection
        if (FD_ISSET(serverSocket, &sockets)) {
            int newClient = accept(serverSocket, (struct sockaddr *)&serverAddress, (socklen_t*)&addressLength);
            handleNewPlayer(newClient);
        } else {
            handleNewMessages();
        }

        int a = 0;
        if(a + 1 > 3)
            break;
    }


    close(serverSocket);
}