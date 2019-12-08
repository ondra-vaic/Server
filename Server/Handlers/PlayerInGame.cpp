//
// Created by me on 12/8/19.
//

#include "PlayerInGame.h"
#include "../NetworkManager.h"

PlayerInGame::PlayerInGame(Player* player, Game* game, State state){
    this->player = player;
    this->game = game;
    this->state = state;
}

void PlayerInGame::ResolveMessage(fd_set* sockets){

    if(!FD_ISSET(player->GetSocketId(), sockets)){
        return;
    }

    bool disconnected = false;
    vector<string> splitMessages = NetworkManager::GetSplitMessages(player->GetSocketId(), &disconnected);

    if(disconnected){
        player->SetDisconnected();
        return;
    }

    for (const string& message : splitMessages) {
        Message* m = new Message(message);

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
        case 'f':
            forfeitWhileWaiting();
    }
}

void PlayerInGame::playing(Message* message){

    switch (message->GetIdentifier())
    {
        case 's':
            if(!game->ResolvePick(message->GetData())){
                player->SetCheating();
                return;
            }
        case 'm':
            if(!game->ResolveMove(message->GetData())){
                player->SetCheating();
                return;
            }
        case 'e':
            game->EndTurn();
        case 'f':
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