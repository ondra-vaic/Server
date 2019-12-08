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

public:
    Player(int playerId);
    int GetSocketId();
    int GetName();
    int GetRoom();
};


#endif //SERVER_PLAYER_H
