//
// Created by me on 12/5/19.
//

#include <vector>
#include "Session.h"
#include "../NetworkManager.h"
#include "../Message.h"

using namespace std;


Session::Session(int player1) : player1(player1)
{
    handler = new Lobby(player1);
}

IMessageHandler* Session::ResolveMessage(Message* message){

    bool disconnected = false;
    vector<string> splitMessages = NetworkManager::GetSplitMessages(player, &disconnected);
    if(disconnected){
        handler = new Disconnect();
        return true;
    }

    for (const string& message : splitMessages) {
        Message* m = new Message(message);
        handler = handler->ResolveMessage(m);
        if(handler == nullptr){
            return false;
        }
    }

    return true;
}

int Session::GetPlayer1() {return player1;}
int Session::GetPlayer2() {return player2;}
void Session::SetPlayer2(int player2){this->player2 = player2;}
void Session::SetPlayer1(int player1){this->player1 = player1;}
