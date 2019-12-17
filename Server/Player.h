//
// Created by me on 12/7/19.
//

#ifndef SERVER_PLAYER_H
#define SERVER_PLAYER_H

#include <string>
#include <bits/stdc++.h>

using namespace std;

class Player {
private:
    int socketId;
    int room;
    string name;
    int sessionId;
    bool disconnected;
    bool cheating;
    bool read;

public:
    explicit Player(int playerId);
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
    void SetRead(bool read);
    bool IsRead();
};

typedef shared_ptr<Player> PlayerPtr;

#endif //SERVER_PLAYER_H
