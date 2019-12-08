//
// Created by me on 11/16/19.
//

#include <vector>
#include <sys/socket.h>
#include "NetworkManager.h"
#include "Handlers/Game.h"
#include "Utils.h"

#define MAX_MESSAGE_LENGTH 255

bool NetworkManager::SendCrown(Player* player, int x, int y){
    return sendMessage(player, "c", to_string(x) + " " + to_string(7 - y));
}

bool NetworkManager::SendMove(Player* player, int x0, int y0, int x1, int y1){
    return sendMessage(player, "m",to_string(x0) + " " + to_string(7 - y0) + " " + to_string(x1) + " " + to_string(7 - y1));
}

bool NetworkManager::SendWake(Player* player){
    return sendMessage(player, "w", "");
}

bool NetworkManager::SendPlace(Player* player, const string& board){
    return sendMessage(player, "p", board);
}

bool NetworkManager::SendDelete(Player* player, int x, int y){
    return sendMessage(player, "d", to_string(x) + " " + to_string(7 - y));
}

bool NetworkManager::SendMessageNumber(Player* player, int num){
    return sendMessage(player, "n", to_string(num));
}

bool NetworkManager::SendLoose(Player* player){
    return sendMessage(player, "l", "");
}

bool NetworkManager::SendWin(Player* player){
    return sendMessage(player, "v", "");
}

bool NetworkManager::SendHello(Player* player) {
    return sendMessage(player, "h", "");
}

bool NetworkManager::sendMessage(Player* player, const string& identifier, const string& message){
    string completeMessage = identifier + message + "|";
    cout << "Sent [" << completeMessage << "]" << "to " << player->GetName() << endl;

    if(send(player->GetSocketId(), completeMessage.c_str(), completeMessage.length(), 0) != 0){
        player->SetDisconnected();
        return false;
    }
    return true;
}

string NetworkManager::GetResponse(int clientId, bool* disconnected){

    string buffer = "";

    while (buffer.back() != '|'){

        char* response = new char[MAX_MESSAGE_LENGTH];
        if(recv(clientId, response, sizeof(response), 0) != 0){
            *disconnected = false;
            return buffer;
        }

        string responseString(response);
        buffer += responseString;
    }

    cout << "<< [" << buffer << "] from " << clientId << endl;
    return buffer;
}


char NetworkManager::GetIdentifier(string message){
    return message[0];
}

string NetworkManager::GetDataPart(const string& message){
    return message.substr(message.find(',') + 1, message.size());
}

int NetworkManager::GetMessageNumber(const string& message)
{
    return stoi(message.substr(1, message.find(',') - 1));
}

vector<string> NetworkManager::GetSplitMessages(int player, bool* disconnected){

    vector<string> splitMessages;

    try {
        string messages = NetworkManager::GetResponse(player, disconnected);

        size_t position = 0;
        string message;
        while ((position = messages.find('|')) != string::npos) {
            message = messages.substr(0, position);
            splitMessages.push_back(message);
            messages.erase(0, position + 1);
        }

    }
    catch( ... ) {
        Utils::Error(-1, "Incorrect message format");
    }

    return splitMessages;
}