//
// Created by me on 11/16/19.
//

#ifndef SERVER_NETWORKMANAGER_H
#define SERVER_NETWORKMANAGER_H

#include <vector>
#include "Game.h"

class NetworkManager {


public:
    static string GetResponse(int clientId);
    static char GetIdentifier(string message);
    static string GetRawMessage(const string& message);
    static int GetMessageNumber(const string& message);
    static vector<string> GetSplitMessages(string messages);
    static void SendCrown(int player, int x, int y);
    static void SendMove(int player, int x0, int y0, int x1, int y1);
    static void SendWake(int player);
    static void SendLoose(int player);
    static void SendWin(int player);
    static void SendPlace(int player, const string& board);
    static void SendDelete(int player, int x, int y);
    static void SendMessageNumber(int player, int num);


private:
    static void sendMessage(int clientId, const string& identifier, const string& message);

};


#endif //SERVER_NETWORKMANAGER_H
