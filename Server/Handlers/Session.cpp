//
// Created by me on 12/5/19.
//

#include "Session.h"
#include "../NetworkManager.h"
#include "../Message.h"
#include "PlayerInGame.h"
#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

Session::Session(const PlayerPtr& player1, const PlayerPtr& player2)
{
    this->game = make_shared<Game>(player1, player2);
    NetworkManager::SendSessionStarted(player1);
    NetworkManager::SendSessionStarted(player2);

    this->player1 = make_shared<PlayerInGame>(player1, game, PlayerInGameState::PLAYING);
    this->player2 = make_shared<PlayerInGame>(player2, game, PlayerInGameState::WAITING);

    this->state = SESSION_ON;
}

void Session::SendPeriodicMessages(){
}

bool Session::TryReconnect(const PlayerPtr& player){

    if(state != SESSION_DISCONNECTED){
        return false;
    }

    if(player->GetName() == disconnectedPlayerName){
        if(player1->GetPlayer()->GetName() == disconnectedPlayerName){
            player1->GetPlayer()->SetSocketId(player->GetSocketId());
            player1->GetPlayer()->ResetErrors();
            player1->ResetState();
            player2->ResetState();
        }
        else{
            player2->GetPlayer()->SetSocketId(player->GetSocketId());
            player2->GetPlayer()->ResetErrors();
            player2->ResetState();
            player1->ResetState();
        }

        state = SESSION_ON;
        return true;
    }

    return false;
}

void Session::ResolveMessage(fd_set* sockets){

    player1->ResolveMessage(sockets);
    player2->ResolveMessage(sockets);

    if(player1->IsPlaying()){
        cout << "player 1 playing " << player1->GetPlayer()->GetSocketId() << " " << player1->GetPlayer()->GetName() << endl;
        resolveGameState(player1, player2);
    }else{
        resolveGameState(player2, player1);
    }

    resolveCheaterLeaver(player1, player2);
    resolveCheaterLeaver(player2, player1);
}

void Session::resolveGameState(const PlayerInGamePtr& playerA, const PlayerInGamePtr& playerB){
    if(game->IsJustWon()){
        NetworkManager::SendLoose(playerB->GetPlayer());
        NetworkManager::SendWin(playerA->GetPlayer());
        state = SESSION_ENDED;
    }

    if(game->HasForfeited()){
        if(playerA->HasForfeited()){
            NetworkManager::SendWin(playerB->GetPlayer());
            NetworkManager::SendLoose(playerA->GetPlayer());
        }else if(playerB->HasForfeited()){
            NetworkManager::SendWin(playerA->GetPlayer());
            NetworkManager::SendLoose(playerB->GetPlayer());
        }

        state = SESSION_ENDED;
    }

    if(game->HasTurnEnded()){
        cout << "*********************** WAKE SEND **************************" << endl;
        NetworkManager::SendWake(playerB->GetPlayer());
        playerA->SetWaiting();
        playerB->SetPlaying();
        game->Switch();
        if(!game->CanMove()){
            NetworkManager::SendLoose(playerB->GetPlayer());
            NetworkManager::SendWin(playerA->GetPlayer());
            state = SESSION_ENDED;
        }
    }
}

void Session::resolveCheaterLeaver(const PlayerInGamePtr& playerA, const PlayerInGamePtr& playerB){
    if(playerA->GetPlayer()->IsCheating()){
        state = SESSION_ENDED;
    }
    if(playerA->GetPlayer()->IsDisconnected() && state != SESSION_DISCONNECTED){
        state = SESSION_DISCONNECTED;
        disconnectedPlayerName = playerA->GetPlayer()->GetName();
        playerA->SetStateBeforeDc();
        playerA->SetDced();

        playerB->SetStateBeforeDc();
        playerB->SetWaitingForReconnect();
    }
}


bool Session::IsEnded(){return state == SESSION_ENDED;}
PlayerInGamePtr Session::GetPlayer1() {return player1;}
PlayerInGamePtr Session::GetPlayer2() {return player2;}
