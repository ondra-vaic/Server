//
// Created by me on 12/6/19.
//

#ifndef SERVER_DISCONNECT_H
#define SERVER_DISCONNECT_H


#include "../Message.h"
#include "Session.h"
#include "IMessageHandler.h"

class Disconnect : public IMessageHandler {

public:
    void ResolveMessage(fd_set* sockets) override;
};


#endif //SERVER_DISCONNECT_H
