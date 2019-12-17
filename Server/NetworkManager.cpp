//
// Created by me on 11/16/19.
//
//
#include <vector>
#include <sys/socket.h>
#include "NetworkManager.h"
#include "Game.h"
#include "Utils.h"
#include "Identifiers.h"


class Room;

#define MAX_MESSAGE_LENGTH 255

bool NetworkManager::SendCrown(const PlayerPtr& player, int x, int y){
    return sendMessage(player, CROWN_FIGURE, to_string(x) + " " + to_string(7 - y));
}

bool NetworkManager::SendMove(const PlayerPtr& player, int x0, int y0, int x1, int y1){
    return sendMessage(player, MOVE_FIGURE,to_string(x0) + " " + to_string(7 - y0) + " " + to_string(x1) + " " + to_string(7 - y1));
}

bool NetworkManager::SendWake(const PlayerPtr& player){
    return sendMessage(player, WAKE_OTHER_PLAYER, "");
}

bool NetworkManager::SendPlace(const PlayerPtr& player, const string& board){
    return sendMessage(player, PLACE_BOARD, board);
}

bool NetworkManager::SendDelete(const PlayerPtr& player, int x, int y){
    return sendMessage(player, DELETE_FIGURE, to_string(x) + " " + to_string(7 - y));
}

bool NetworkManager::SendMessageNumber(const PlayerPtr& player, int num){
    return sendMessage(player, 'n', to_string(num));
}

bool NetworkManager::SendLoose(const PlayerPtr& player){
    return sendMessage(player, LOOSE, "");
}

bool NetworkManager::SendWin(const PlayerPtr& player){
    return sendMessage(player, WIN, "");
}

bool NetworkManager::SendHello(const PlayerPtr& player){
    return sendMessage(player, 'h', "");
}

bool NetworkManager::SendConfirmName(const PlayerPtr& player){
    return sendMessage(player, NAME_CONFIRM, "");
}

bool NetworkManager::SendDenyName(const PlayerPtr& player){
    return sendMessage(player, NAME_DENY, "");
}

bool NetworkManager::SendRoomsInfo(const PlayerPtr& player, vector<array<int, 3>>& roomsOccupation){

    vector<array<int, 3>> a;

    string message;
    for (auto& roomOccupation : roomsOccupation) {
        message += to_string(roomOccupation[0]) + " "
                + to_string(roomOccupation[1]) + " "
                + to_string(roomOccupation[2]) + ",";
    }

    message = message.substr(0, message.size() - 1);

    return sendMessage(player, ROOMS_INFO, message);
}

bool NetworkManager::SendRoomInfo(const PlayerPtr& player, array<int, 3>& roomOccupation){

    vector<array<int, 3>> a;

    string message = to_string(roomOccupation[0]) + " "
                   + to_string(roomOccupation[1]) + " "
                   + to_string(roomOccupation[2]) + ",";

    message = message.substr(0, message.size() - 1);

    return sendMessage(player, ROOM_INFO, message);
}

bool NetworkManager::sendMessage(const PlayerPtr& player, char identifier, const string& message){
    string completeMessage = string(1, identifier) + message + "|";
    cout << "Sent [" << completeMessage << "]" << "to " << player->GetName() << endl;

    if(send(player->GetSocketId(), completeMessage.c_str(), completeMessage.length(), 0) <= 0){
        player->SetDisconnected();
        return false;
    }
    return true;
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