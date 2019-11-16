//
// Created by me on 11/16/19.
//

#include <vector>
#include <sys/socket.h>
#include "NetworkManager.h"
#include "Game.h"

#define MAX_MESSAGE_LENGTH 255

string NetworkManager::GetResponse(int clientId){

    string buffer = "";

    while (buffer.back() != '|'){

        char* response = new char[MAX_MESSAGE_LENGTH];
        recv(clientId, response, sizeof(response), 0);
        string responseString(response);
        buffer += responseString;
    }

    cout << "<< [" << buffer << "] from " << clientId << endl;
    return buffer;
}

void NetworkManager::SendMove(int player, int x0, int y0, int x1, int y1){
    sendMessage(player, "m",to_string(x0) + " " + to_string(y0) + " " + to_string(x1) + " " + to_string(y1));
}

void NetworkManager::SendWake(int player){
    sendMessage(player, "w", "");
}

void NetworkManager::SendPlace(int player, const string& board){
    sendMessage(player, "p", board);
}

void NetworkManager::SendDelete(int player, int x, int y){
    sendMessage(player, "d", to_string(x) + " " + to_string(y));
}

void NetworkManager::sendMessage(int clientId, const string& identifier, const string& message){

    string completeMessage = identifier + message + "|";
    send(clientId, completeMessage.c_str(), completeMessage.length(), 0);\

    cout << "Sent [" << completeMessage << "]" << "to " << clientId << endl;
}

char NetworkManager::GetIdentifier(string message){
    return message[0];
}

string NetworkManager::GetRawMessage(const string& message){
    return message.substr(1, message.size());
}

vector<string> NetworkManager::GetSplitMessages(string messages){
    vector<string> splitMessages;

    size_t position = 0;
    string message;
    while ((position = messages.find('|')) != string::npos) {
        message = messages.substr(0, position);
        splitMessages.push_back(message);
        messages.erase(0, position + 1);
    }

    //splitMessages.pop_back();

    return splitMessages;
}