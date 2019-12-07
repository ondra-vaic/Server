//
// Created by me on 12/5/19.
//

#ifndef SERVER_LOBBY_H
#define SERVER_LOBBY_H


#include "../Message.h"
#include "Session.h"
#include "IMessageHandler.h"

class Lobby : public IMessageHandler{

private:
    int player1;

public:
    explicit Lobby(int player1);
    IMessageHandler* ResolveMessage(Message* message);
};


#endif //SERVER_LOBBY_H
