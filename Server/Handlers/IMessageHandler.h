//
// Created by me on 12/6/19.
//

#ifndef SERVER_IMESSAGEHANDLER_H
#define SERVER_IMESSAGEHANDLER_H


#include <sys/select.h>

class IMessageHandler{
public:
    virtual void ResolveMessage(fd_set* sockets) {}
    virtual void SendPeriodicMessages() {};
};

#endif
