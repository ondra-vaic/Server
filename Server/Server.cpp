//
// Created by me on 12/6/19.
//

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <vector>
#include "Game.h"
#include "Utils.h"
#include "Server.h"
#include <chrono>

int Server::numberOfConnectedPlayers(){
    int count = playerSetups.size();
    for (auto& room : rooms) {
        count += room->GetPlayers().size();
    }
    return count;
}

vector<PlayerPtr> Server::getAllPlayers(){
    vector<PlayerPtr> socketIds;

    for(auto& player : playerSetups){
        socketIds.push_back(player->GetPlayer());
    }

    for(auto& room : rooms){
        for(auto& player : room->GetPlayers()){
            socketIds.push_back(player);
        }
    }

    return socketIds;
}

int Server::setSocketSet(){
    int maxSocket = -1;
    for (PlayerPtr player : getAllPlayers()) {
        FD_SET(player->GetSocketId(), &sockets);
        player->SetRead(false);
        cout << "setting " << player->GetSocketId() << " " << player->GetName() << endl;
        maxSocket = max(player->GetSocketId(), maxSocket);
    }

    return maxSocket;
}

void Server::handleNewPlayer(int newPlayer){

    if(newPlayer < 0){
        Utils::Error(-1, "Failed to accept connection");
    }

    cout << "Accepting new.." << endl;

    if(numberOfConnectedPlayers() < maxPlayers){
        PlayerSetupPtr playerSetupPtr(make_shared<PlayerSetup>(make_shared<Player>(newPlayer), rooms, names, PlayerSetupState::SETTING_NAME));
        playerSetups.push_back(playerSetupPtr);
    }
    else{
        //Send msg and kick
        //TODO kick

        close(newPlayer);
    }
}

void Server::resolveSetUps(){
    for(auto& playerSetUp : playerSetups){
        playerSetUp->ResolveMessage(&sockets);

        if(playerSetUp->GetPlayer()->IsDisconnected() || playerSetUp->GetPlayer()->IsCheating() || playerSetUp->IsPlayerToLeave()){
            close(playerSetUp->GetPlayer()->GetSocketId());
            continue;
        }

        //add player to room
        if(playerSetUp->IsPlayerInitialized()){
            PlayerPtr player = playerSetUp->GetPlayer();
            rooms[player->GetRoom()]->SetPlayer(player);
        }
    }

    //remove added players from setups
    Utils::RemoveIf(playerSetups,[](const PlayerSetupPtr& p){
        return p->IsPlayerInitialized() || p->GetPlayer()->IsDisconnected() || p->GetPlayer()->IsCheating();
    });
}

void Server::resolveRooms(){
    for (auto& room : rooms)
    {
        room->ResolveMessage(&sockets);
        vector<PlayerSetupPtr> playersToChooseNewRoom;

        for(auto& player : room->GetPlayersToLeave()){
            PlayerSetupPtr playerSetupPtr(new PlayerSetup(player, rooms, names, PlayerSetupState::CHOOSING_ROOM));
            playersToChooseNewRoom.push_back(playerSetupPtr);
        }

        playerSetups.insert(playerSetups.end(), playersToChooseNewRoom.begin(), playersToChooseNewRoom.end());
    }
}

void Server::SendPeriodicMessages(){

    for(auto& player : playerSetups){
        player->SendPeriodicMessages();
    }

    for(auto& room : rooms){
        room->SendPeriodicMessages();
    }
}

void Server::ResolveMessage(fd_set* sockets){
    cout << "Receiving messages.." << endl;

    resolveSetUps();
    resolveRooms();
    SendPeriodicMessages();
}

Server::Server(int maxPlayers, int maxPendingConnections, int port, int numberOfRooms){

    this->maxPlayers = maxPlayers;
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
        rooms.push_back(make_shared<Room>());
    }
}

void Server::MainLoop(){

    while (true) {
        //clear the socket set
        FD_ZERO(&sockets);

        //add master socket to set
        FD_SET(serverSocket, &sockets);

        cout << "Setting socket set.." << endl;

        int maxClientSocket = setSocketSet();
        maxSocket = max(serverSocket, maxClientSocket);

        cout << "Waiting for activity.." <<  " max is " << maxSocket << endl;

        //wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
        int activity = select(maxSocket + 1, &sockets, nullptr, nullptr, nullptr);

        cout << "Resolving Activity.." << endl;
        if (errno != EINTR) {
            if(activity < 0){
                Utils::Error(activity, "select error");
            }
        }

        //If something happened on the master socket , then its an incoming connection
        if (FD_ISSET(serverSocket, &sockets)) {
            int newClient = accept(serverSocket, (struct sockaddr *)&serverAddress, (socklen_t*)&addressLength);
            handleNewPlayer(newClient);
        }

        ResolveMessage(&sockets);
//
//        int time = Utils::GetCurrentTime();
//
//        if(lastPeriodicMessageTime + 100 < time)
//        {
//            lastPeriodicMessageTime = time;
//            SendPeriodicMessages();
//        }
        int a = 0;
        if(a + 1 > 3)
            break;
    }

    close(serverSocket);
}

