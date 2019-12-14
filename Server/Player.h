//
// Created by me on 12/7/19.
//

#ifndef SERVER_PLAYER_H
#define SERVER_PLAYER_H

#include <string>
using namespace std;

class Player {

private:
    int socketId;
    int room;
    string name;
    int sessionId;
    bool disconnected;
    bool cheating;


public:
    Player(int playerId);
    int GetSocketId();
    string GetName();
    int GetSessionId();
    int GetRoom();
    bool IsCheating();
    bool IsDisconnected();

    void SetName(const string& name);
    void SetRoom(int room);
    void SetSessionId(int sessionId);
    void SetDisconnected();
    void SetCheating();
};


#endif //SERVER_PLAYER_H
