//
// Created by me on 12/6/19.
//

#ifndef SERVER_ROOM_H
#define SERVER_ROOM_H

#include <vector>
#include "IMessageHandler.cpp"

class Room : public IMessageHandler {

public:
    int NumPlayers();
    vector<int> GetPlayers();
    IMessageHandler* ResolveMessage(Message* message);
};


#endif //SERVER_ROOM_H
