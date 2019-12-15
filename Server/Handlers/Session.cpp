//
// Created by me on 12/5/19.
//

#include <vector>
#include "Session.h"
#include "../NetworkManager.h"
#include "../Message.h"
#include "PlayerInGame.h"

Session::Session(Player* player1, Player* player2)
{
    this->game = new Game(player1, player2);
    this->player1 = new PlayerInGame(player1, game, PlayerInGame::PLAYING);
    this->player2 = new PlayerInGame(player2, game, PlayerInGame::WAITING);
    this->state = SESSION_ON;
}

void Session::SendPeriodicMessages(){
    player1->SendPeriodicMessages();
    player2->SendPeriodicMessages();
}

void Session::ResolveMessage(fd_set* sockets){
    player1->ResolveMessage(sockets);
    player2->ResolveMessage(sockets);

    resolveCheaterLeaver(player1->GetPlayer());
    resolveCheaterLeaver(player2->GetPlayer());
}

void Session::resolveCheaterLeaver(Player* player){
    if(player->IsCheating()){

    }
}

bool Session::IsEnded(){return state == SESSION_ENDED;}
PlayerInGame* Session::GetPlayer1() {return player1;}
PlayerInGame* Session::GetPlayer2() {return player2;}
