//
// Created by me on 12/6/19.
//

#include "../Message.h"

class IMessageHandler{
public:
    virtual void ResolveMessage(fd_set* sockets);
};