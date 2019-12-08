//
// Created by me on 12/5/19.
//

#include <vector>
#include "Session.h"
#include "../NetworkManager.h"
#include "../Message.h"

using namespace std;


Session::Session(Player* player1, Player* player2)
{
    Game* game = new Game();

    this->player1 = new PlayerInGame(player1, game);
    this->player2 = player2;
}

void Session::ResolveMessage(fd_set* sockets){
    player1->ResolveMessage();
    player2->ResolveMessage();
}

bool Session::IsEnded(){return state == SESSION_ENDED;}
PlayerInGame* Session::GetPlayer1() {return player1;}
PlayerInGame* Session::GetPlayer2() {return player2;}
