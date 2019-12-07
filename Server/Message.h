//
// Created by me on 12/6/19.
//

#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H

#include <string>
using namespace std;

class Message {

private:
    char identifier;
    int messageNumber;
    string rawMessage;
    string data;


public:
    explicit Message(const string& rawMessage);
    char GetIdentifier();
    int GetMessageNumber();
    string GetRawMessage();
    string GetData();

};


#endif //SERVER_MESSAGE_H
