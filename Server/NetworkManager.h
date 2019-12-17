//
// Created by me on 11/16/19.
//

#ifndef SERVER_NETWORKMANAGER_H
#define SERVER_NETWORKMANAGER_H

#include <vector>
#include "Game.h"
#include <array>

class NetworkManager {


public:
    static string GetResponse(const PlayerPtr& player);
    static char GetIdentifier(string message);
    static string GetDataPart(const string& message);
    static int GetMessageNumber(const string& message);
    static vector<string> GetSplitMessages(const PlayerPtr& player);

    static bool SendCrown(const PlayerPtr& player, int x, int y);
    static bool SendMove(const PlayerPtr& player, int x0, int y0, int x1, int y1);
    static bool SendWake(const PlayerPtr& player);
    static bool SendLoose(const PlayerPtr& player);
    static bool SendWin(const PlayerPtr& player);
    static bool SendPlace(const PlayerPtr& player, const string& board);
    static bool SendDelete(const PlayerPtr& player, int x, int y);
    static bool SendMessageNumber(const PlayerPtr& player, int num);
    static bool SendHello(const PlayerPtr& player);
    static bool SendConfirmName(const PlayerPtr& player);
    static bool SendDenyName(const PlayerPtr& player);
    static bool SendRoomsInfo(const PlayerPtr& player, vector<array<int, 3>>& roomsOccupation);
    static bool SendRoomInfo(const PlayerPtr& player, array<int, 3>& roomsOccupation);

private:
    static bool sendMessage(const PlayerPtr& player, char identifier, const string& message);

};


#endif //SERVER_NETWORKMANAGER_H
