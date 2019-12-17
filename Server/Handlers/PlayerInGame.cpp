//
// Created by me on 12/8/19.
//

#include "PlayerInGame.h"
#include "../NetworkManager.h"
#include "../Identifiers.h"
#include <bits/stdc++.h>

using namespace std;

PlayerInGame::PlayerInGame(PlayerPtr player, GamePtr game, PlayerInGameState state)
    : LeafHandler<PlayerInGameState, PlayerInGame>(move(player)), game(move(game)){
    this->state = state;
}

void PlayerInGame::init(){
    commands[PLAYING][SELECT_FIGURE] = bind(&PlayerInGame::resolvePick, this, _1);
    commands[PLAYING][MOVE_FIGURE] = bind(&PlayerInGame::resolveMove, this, _1);
    commands[PLAYING][END_TURN] = bind(&PlayerInGame::endTurn, this, _1);
    commands[PLAYING][FORFEIT] = bind(&PlayerInGame::setForfeited, this, _1);

    commands[WAITING][FORFEIT] = bind(&PlayerInGame::forfeitWhileWaiting, this, _1);
}

void PlayerInGame::SendPeriodicMessages(){
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

bool PlayerInGame::resolvePick(const MessagePtr& message){
    return game->ResolvePick(message->GetData());
}

bool PlayerInGame::resolveMove(const MessagePtr& message){
    return game->ResolveMove(message->GetData());
}

bool PlayerInGame::endTurn(const MessagePtr& message){
    return game->EndTurn(message->GetData());
}

bool PlayerInGame::setForfeited(const MessagePtr& message){
    return game->SetForfeited(message->GetData());
}

bool PlayerInGame::forfeitWhileWaiting(const MessagePtr& message){
    NetworkManager::SendLoose(game->GetOtherPlayer());
    NetworkManager::SendWin(game->GetCurrentPlayer());
}

