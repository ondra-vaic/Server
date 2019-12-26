//
// Created by me on 12/8/19.
//

#include "PlayerInGame.h"
#include "../NetworkManager.h"
#include "../Identifiers.h"
#include <bits/stdc++.h>

using namespace std;

PlayerInGame::PlayerInGame(const PlayerPtr& player, const GamePtr& game, PlayerInGameState state)
    : LeafHandler<PlayerInGameState, PlayerInGame>(player), game(game){
    this->state = state;
    this->stateBeforeDc = state;
    NetworkManager::SendEnemyName(player, game->GetOtherPlayer(player)->GetName());
}

void PlayerInGame::init(){
    commands[PLAYING][SELECT_FIGURE] = bind(&PlayerInGame::resolvePick, this, _1);
    commands[PLAYING][MOVE_FIGURE] = bind(&PlayerInGame::resolveMove, this, _1);
    commands[PLAYING][END_TURN] = bind(&PlayerInGame::endTurn, this, _1);
    commands[PLAYING][FORFEIT] = bind(&PlayerInGame::setForfeited, this, _1);
    commands[PLAYING][GAME_INFO] = bind(&PlayerInGame::sendInfo, this, _1);

    commands[WAITING][FORFEIT] = bind(&PlayerInGame::setForfeited, this, _1);
    commands[WAITING][GAME_INFO] = bind(&PlayerInGame::sendInfo, this, _1);
}

void PlayerInGame::ResetState(){
    state = stateBeforeDc;
}

void PlayerInGame::SetStateBeforeDc(){
    stateBeforeDc = state;
}

void PlayerInGame::SetWaitingForReconnect(){
    state = WAITING_RECONNECT;
}

void PlayerInGame::SetDced(){
    state = DISCONNECTED;
}

void PlayerInGame::SetWaiting(){
    state = WAITING;
}

void PlayerInGame::SetPlaying(){
    state = PLAYING;
}

bool PlayerInGame::IsPlaying(){
    return state == PLAYING;
}

bool PlayerInGame::IsWaiting(){
    return state == WAITING;
}

bool PlayerInGame::HasForfeited(){
    return state == FORFEITED;
}

bool PlayerInGame::resolvePick(const MessagePtr& message){
    cout << "----------------------- resolving pick ---------------"<< endl;
    return game->ResolvePick(message->GetData());
}

bool PlayerInGame::sendInfo(const MessagePtr& message){

    if(state == PLAYING){
        NetworkManager::SendWake(player);
        NetworkManager::SendPlace(player, game->GetBoard()->BoardToString());
    }else{
        game->GetBoard()->FlipBoard();
        NetworkManager::SendPlace(player, game->GetBoard()->BoardToString());
        game->GetBoard()->FlipBoard();
    }

    return message->GetData().empty();
}

bool PlayerInGame::resolveMove(const MessagePtr& message){
    return game->ResolveMove(message->GetData());;
}

bool PlayerInGame::endTurn(const MessagePtr& message){
    return game->EndTurn(message->GetData());
}

bool PlayerInGame::setForfeited(const MessagePtr& message){
    if(game->SetForfeited(message->GetData())){
        state = FORFEITED;
        return true;
    }
    return false;
}

