//
// Created by me on 12/6/19.
//

#ifndef SERVER_DISCONNECT_H
#define SERVER_DISCONNECT_H


#include "../Message.h"
#include "Session.h"
#include "IMessageHandler.cpp"

class Disconnect : public IMessageHandler {

public:
    IMessageHandler* ResolveMessage(Message* message);
};


#endif //SERVER_DISCONNECT_H
