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
    static void GetResponse(const PlayerPtr& player);
    static char GetIdentifier(string message);
    static string GetDataPart(const string& message);
    static int GetMessageNumber(const string& message);

    static void SendCrown(const PlayerPtr& player, int x, int y);
    static void SendMove(const PlayerPtr& player, int x0, int y0, int x1, int y1);
    static void SendWake(const PlayerPtr& player);
    static void SendLoose(const PlayerPtr& player);
    static void SendWin(const PlayerPtr& player);
    static void SendPlace(const PlayerPtr& player, const string& board);
    static void SendDelete(const PlayerPtr& player, int x, int y);
    static void SendMessageNumber(const PlayerPtr& player, int num);
    static void SendHello(const PlayerPtr& player);
    static void SendIsReconnected(const PlayerPtr& player);
    static void SendConfirmName(const PlayerPtr& player);
    static void SendDenyName(const PlayerPtr& player);
    static void SendRoomsInfo(const PlayerPtr& player, vector<array<int, 3>>& roomsOccupation);
    static void SendRoomInfo(const PlayerPtr& player, array<int, 3>& roomsOccupation);
    static void SendSessionStarted(const PlayerPtr& player);
    static void SendEnemyName(const PlayerPtr& player, const string &oponentName);
    static void SendConfirm(const PlayerPtr& player, int number);
    static void SendConfirmRoom(const PlayerPtr& player);
    static void SendConfirmBackFromSetup(const PlayerPtr& player);
    static void SendConfirmBackFromRoom(const PlayerPtr& player);
    static void SendOponentDc(const PlayerPtr& player);
    static void SendOponentRc(const PlayerPtr& player);

    static void SendPick(const PlayerPtr& player, int x, int y);
    static void SendConfirmPick(const PlayerPtr& player, int x, int y);
    static void SendConfirmMove(const PlayerPtr& player, int x0, int y0, int x1, int y1);
    static void SendConfirmEndMove(const PlayerPtr& player);

private:
    static void sendMessage(const PlayerPtr& player, char identifier, const string& message);
};


#endif //SERVER_NETWORKMANAGER_H
