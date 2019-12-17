//
// Created by me on 12/5/19.
//

#include "Session.h"
#include "../NetworkManager.h"
#include "../Message.h"
#include "PlayerInGame.h"
#include <bits/stdc++.h>
using namespace std;

Session::Session(const PlayerPtr& player1, const PlayerPtr& player2)
{
    this->game = make_shared<Game>(player1, player2);
    this->player1 = make_shared<PlayerInGame>(player1, game, PlayerInGameState::PLAYING);
    this->player2 = make_shared<PlayerInGame>(player2, game, PlayerInGameState::WAITING);
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

void Session::resolveCheaterLeaver(const PlayerPtr& player){
    if(player->IsCheating()){
        state = SESSION_ENDED;
    }
}


bool Session::IsEnded(){return state == SESSION_ENDED;}
PlayerInGamePtr Session::GetPlayer1() {return player1;}
PlayerInGamePtr Session::GetPlayer2() {return player2;}
