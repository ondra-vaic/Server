//
// Created by me on 11/16/19.
//
//
#include <vector>
#include <sys/socket.h>
#include <unistd.h>
#include "NetworkManager.h"
#include "Game.h"
#include "Utils.h"
#include "Identifiers.h"


class Room;

#define MAX_MESSAGE_LENGTH 255

void NetworkManager::SendCrown(const PlayerPtr& player, int x, int y){
    return sendMessage(player, CROWN_FIGURE, to_string(x) + " " + to_string(7 - y));
}

void NetworkManager::SendMove(const PlayerPtr& player, int x0, int y0, int x1, int y1){
     sendMessage(player, MOVE_FIGURE,to_string(x0) + " " + to_string(7 - y0) + " " + to_string(x1) + " " + to_string(7 - y1));
}

void NetworkManager::SendWake(const PlayerPtr& player){
     sendMessage(player, WAKE_OTHER_PLAYER, "");
}

void NetworkManager::SendPlace(const PlayerPtr& player, const string& board){
     sendMessage(player, PLACE_BOARD, board);
}

void NetworkManager::SendDelete(const PlayerPtr& player, int x, int y){
     sendMessage(player, DELETE_FIGURE, to_string(x) + " " + to_string(7 - y));
}

void NetworkManager::SendMessageNumber(const PlayerPtr& player, int num){
     sendMessage(player, 'n', to_string(num));
}

void NetworkManager::SendLoose(const PlayerPtr& player){
     sendMessage(player, LOOSE, "");
}

void NetworkManager::SendWin(const PlayerPtr& player){
     sendMessage(player, WIN, "");
}

void NetworkManager::SendHello(const PlayerPtr& player){
     sendMessage(player, 'h', "");
}

void NetworkManager::SendConfirmName(const PlayerPtr& player){
     sendMessage(player, NAME_CONFIRM, "");
}

void NetworkManager::SendDenyName(const PlayerPtr& player){
    sendMessage(player, NAME_DENY, "");
}

void NetworkManager::SendIsReconnected(const PlayerPtr& player){
    sendMessage(player, RECONNECTED, "");
}

void NetworkManager::SendRoomsInfo(const PlayerPtr& player, vector<array<int, 3>>& roomsOccupation){

    vector<array<int, 3>> a;

    string message;
    for (auto& roomOccupation : roomsOccupation) {
        message += to_string(roomOccupation[0]) + " "
                + to_string(roomOccupation[1]) + " "
                + to_string(roomOccupation[2]) + ",";
    }

    message = message.substr(0, message.size() - 1);

     sendMessage(player, ROOMS_INFO, message);
}

void NetworkManager::SendRoomInfo(const PlayerPtr& player, array<int, 3>& roomOccupation){

    vector<array<int, 3>> a;

    string message = to_string(roomOccupation[0]) + " "
                   + to_string(roomOccupation[1]) + " "
                   + to_string(roomOccupation[2]) + ",";

    message = message.substr(0, message.size() - 1);

     sendMessage(player, ROOM_INFO, message);
}

void NetworkManager::SendSessionStarted(const PlayerPtr& player){
    sendMessage(player, SESSION_STARTED, "");
}

void NetworkManager::SendEnemyName(const PlayerPtr& player, const string& oponentName){
    sendMessage(player, ENEMY_NAME, oponentName);
}

void NetworkManager::sendMessage(const PlayerPtr& player, char identifier, const string& message){
    string completeMessage = string(1, identifier) + message + "|";
    cout << "Sent [" << completeMessage << "]" << " to " << player->GetName() << " " << player->GetSocketId() << endl;

    if(send(player->GetSocketId(), completeMessage.c_str(), completeMessage.length(), 0) <= 0){
        player->SetDisconnected();
    }
}

string NetworkManager::GetResponse(const PlayerPtr& player){

    string buffer;

    while (buffer.back() != '|'){

        char* response = new char[MAX_MESSAGE_LENGTH];
        if(recv(player->GetSocketId(), response, sizeof(response), 0) <= 0){
            player->SetDisconnected();
            return buffer;
        }

        if(buffer.length() > 1024){
            player->SetCheating();
            return buffer;
        }

        string responseString(response);
        buffer += responseString;
    }

    cout << "<< [" << buffer << "] from " << player->GetName() << " " << player->GetSocketId() << endl;
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

vector<string> NetworkManager::GetSplitMessages(const PlayerPtr& player){

    vector<string> splitMessages;
    string messages = NetworkManager::GetResponse(player);

    if(player->IsDisconnected() || player->IsCheating())
        return splitMessages;

    try {
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