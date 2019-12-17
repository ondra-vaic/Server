//
// Created by me on 12/6/19.
//

#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H

#include <string>
#include "Player.h"

using namespace std;

class Message {

private:
    char identifier;
    int messageNumber;
    string rawMessage;
    string data;

public:
    explicit Message(const string& rawMessage, const PlayerPtr& player);
    char GetIdentifier();
    int GetMessageNumber();
    string GetRawMessage();
    string GetData();

};

typedef shared_ptr<Message> MessagePtr;

#endif //SERVER_MESSAGE_H
