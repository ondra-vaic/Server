//
// Created by me on 11/16/19.
//

#include <vector>
#include <sys/socket.h>
#include "NetworkManager.h"
#include "Handlers/Game.h"
#include "Utils.h"

#define MAX_MESSAGE_LENGTH 255

void NetworkManager::SendCrown(int player, int x, int y){
    sendMessage(player, "c", to_string(x) + " " + to_string(7 - y));
}

void NetworkManager::SendMove(int player, int x0, int y0, int x1, int y1){
    sendMessage(player, "m",to_string(x0) + " " + to_string(7 - y0) + " " + to_string(x1) + " " + to_string(7 - y1));
}

void NetworkManager::SendWake(int player){
    sendMessage(player, "w", "");
}

void NetworkManager::SendPlace(int player, const string& board){
    sendMessage(player, "p", board);
}

void NetworkManager::SendDelete(int player, int x, int y){
    sendMessage(player, "d", to_string(x) + " " + to_string(7 - y));
}

void NetworkManager::SendMessageNumber(int player, int num){
    sendMessage(player, "n", to_string(num));
}

void NetworkManager::SendLoose(int player){
    sendMessage(player, "l", "");
}

void NetworkManager::SendWin(int player){
    sendMessage(player, "v", "");
}

void NetworkManager::SendHello(int player) {
    sendMessage(player, "h", "");
}

void NetworkManager::sendMessage(int clientId, const string& identifier, const string& message){

    string completeMessage = identifier + message + "|";
    send(clientId, completeMessage.c_str(), completeMessage.length(), 0);

    cout << "Sent [" << completeMessage << "]" << "to " << clientId << endl;
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
        string messages = NetworkManager::GetResponse(player);

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