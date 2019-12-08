//
// Created by me on 11/16/19.
//

#ifndef SERVER_NETWORKMANAGER_H
#define SERVER_NETWORKMANAGER_H

#include <vector>
#include "Handlers/Game.h"

class NetworkManager {


public:
    static string GetResponse(int clientId, bool* disconnected);
    static char GetIdentifier(string message);
    static string GetDataPart(const string& message);
    static int GetMessageNumber(const string& message);
    static vector<string> GetSplitMessages(int player, bool* disconnected);

    static bool SendCrown(Player* player, int x, int y);
    static bool SendMove(Player* player, int x0, int y0, int x1, int y1);
    static bool SendWake(Player* player);
    static bool SendLoose(Player* player);
    static bool SendWin(Player* player);
    static bool SendPlace(Player* player, const string& board);
    static bool SendDelete(Player* player, int x, int y);
    static bool SendMessageNumber(Player* player, int num);
    static bool SendHello(Player* player);

private:
    static bool sendMessage(Player* player, const string& identifier, const string& message);

};


#endif //SERVER_NETWORKMANAGER_H
