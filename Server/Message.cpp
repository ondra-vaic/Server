//
// Created by me on 12/6/19.
//


#include <unistd.h>
#include "Message.h"
#include "NetworkManager.h"
#include "Utils.h"


Message::Message(const string& rawMessage, const PlayerPtr& player){
    try {
        this->rawMessage = rawMessage;
        this->messageNumber = NetworkManager::GetMessageNumber(rawMessage);
        this->identifier = NetworkManager::GetIdentifier(rawMessage);
        this->data = NetworkManager::GetDataPart(rawMessage);
    }
    catch ( ... ){
        player->SetCheating();
        //Utils::Error(-1, "Error parsing message");
    }
}

char Message::GetIdentifier(){
    return identifier;
}

string Message::GetRawMessage(){
    return rawMessage;
}

string Message::GetData(){
    return data;
}

int Message::GetMessageNumber(){
    return messageNumber;
}

