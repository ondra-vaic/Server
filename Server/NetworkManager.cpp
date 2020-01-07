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

void NetworkManager::SendConfirmMove(const PlayerPtr& player, int x0, int y0, int x1, int y1){
    sendMessage(player, CONFIRM_MOVE, to_string(x0) + " " + to_string(y0) + " " + to_string(x1) + " " + to_string(y1));
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

void NetworkManager::SendOponentDc(const PlayerPtr& player){
    sendMessage(player, OPONENT_DC, "");
}

void NetworkManager::SendOponentRc(const PlayerPtr& player){
    sendMessage(player, OPONENT_RC, "");
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

void NetworkManager::SendPick(const PlayerPtr& player, int x, int y){
    sendMessage(player, SELECT_FIGURE, to_string(x) + " " + to_string(7 - y));
}

void NetworkManager::SendConfirmPick(const PlayerPtr& player, int x, int y){
    sendMessage(player, CONFIRM_SELECT, to_string(x) + " " + to_string(y));
}

void NetworkManager::SendConfirmEndMove(const PlayerPtr& player){
    sendMessage(player, CONFIRM_END_TURN, "");
}

void NetworkManager::sendMessage(const PlayerPtr& player, char identifier, const string& message){
    string completeMessage = string(1, identifier) + message + "|";

    if(identifier != NUMBER_CONFIRM)
        cout << "Sent [" << completeMessage << "]" << " to " << player->GetName() << " " << player->GetSocketId() << endl;

    if(send(player->GetSocketId(), completeMessage.c_str(), completeMessage.length(), 0) <= 0){
        player->SetDisconnected();
    }
}

void NetworkManager::GetResponse(const PlayerPtr& player){

    string buffer;

    char* response = new char[MAX_MESSAGE_LENGTH];

    if(recv(player->GetSocketId(), response, sizeof(response), 0) <= 0){
        cout << "Empty message player will be disconnected..." << endl;
        player->SetDisconnected();
    }

    if(buffer.length() > 1024){
        player->SetCheating();
    }

    string responseString(response);
    player->ConcatenateToBuffer(responseString);

    if(responseString[0] != PING)
        cout << "<< [" << responseString << "] from " << player->GetName() << " " << player->GetSocketId() << endl;
}

void NetworkManager::SendConfirm(const PlayerPtr& player, int number){
    sendMessage(player, NUMBER_CONFIRM, to_string(number));
}

void NetworkManager::SendConfirmRoom(const PlayerPtr& player){
    sendMessage(player, CONFIRM_ROOM, "");
}

void NetworkManager::SendConfirmBackFromSetup(const PlayerPtr& player){
    sendMessage(player, CONFIRM_LEAVE_ROOMS_LOBBY, "");
}

void NetworkManager::SendConfirmBackFromRoom(const PlayerPtr& player){
    sendMessage(player, CONFIRM_LEAVE_ROOM, "");
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