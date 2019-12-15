//
// Created by me on 12/8/19.
//

#include "PlayerInGame.h"
#include "../NetworkManager.h"
#include "../Identifiers.h"

PlayerInGame::PlayerInGame(Player* player, Game* game, State state){
    this->player = player;
    this->game = game;
    this->state = state;
}

void PlayerInGame::SendPeriodicMessages(){
    SendPeriodicMessages();
}

void PlayerInGame::ResolveMessage(fd_set* sockets){

    if(!FD_ISSET(player->GetSocketId(), sockets)){
        return;
    }

    vector<string> splitMessages = NetworkManager::GetSplitMessages(player);

    if(player->IsDisconnected()){
        return;
    }

    for (const string& message : splitMessages) {
        Message* m = new Message(message, player);

        switch(state){
            case PLAYING:
                playing(m);
                continue;
            case WAITING:
                waiting(m);
                continue;
            default:
                player->SetCheating();
                return;
        }
    }
}

void PlayerInGame::waiting(Message *message) {
    switch (message->GetIdentifier())
    {
        case FORFEIT:
            forfeitWhileWaiting();
    }
}

void PlayerInGame::playing(Message* message){

    switch (message->GetIdentifier())
    {
        case SELECT_FIGURE:
            if(!game->ResolvePick(message->GetData())){
                player->SetCheating();
                return;
            }
        case MOVE_FIGURE:
            if(!game->ResolveMove(message->GetData())){
                player->SetCheating();
                return;
            }
        case END_TURN:
            game->EndTurn();
        case FORFEIT:
            game->SetForfeited();
    }

    if(game->IsJustWon()){
        NetworkManager::SendLoose(game->GetOtherPlayer());
        NetworkManager::SendWin(game->GetCurrentPlayer());
        state = WON;
    }

    if(game->HasForfeited()){
        NetworkManager::SendLoose(game->GetCurrentPlayer());
        NetworkManager::SendWin(game->GetOtherPlayer());
        state = LOST;
    }

    if(game->HasTurnEnded()){
        game->Switch();
        state = WAITING;
        if(!game->CanMove()){
            NetworkManager::SendLoose(game->GetCurrentPlayer());
            NetworkManager::SendWin(game->GetOtherPlayer());
            state = WON;
        }
    }
}

void PlayerInGame::forfeitWhileWaiting(){
    NetworkManager::SendLoose(game->GetOtherPlayer());
    NetworkManager::SendWin(game->GetCurrentPlayer());
}

Player* PlayerInGame::GetPlayer(){
    return player;
}