//
// Created by me on 12/6/19.
//

#include <algorithm>
#include "Room.h"
#include "../Utils.h"
#include <bits/stdc++.h>
using namespace std;

void Room::ResolveMessage(fd_set* sockets){
    resolvePlayersInRoom(sockets);
    resolveSessions(sockets);
}

void Room::SendPeriodicMessages(){
    for(auto& player : playersInRoom){
        player->SendRoomInfo(GetPlayersToJoinGame().size(), GetPlayersInSessions().size(), GetWaitingPlayers().size());
    }
    for(auto& session : sessions){
        session->SendPeriodicMessages();
    }
}

void Room::resolvePlayersInRoom(fd_set* sockets){

    playersToLeave.clear();

    for(auto& playerInRoom : playersInRoom){
        playerInRoom->ResolveMessage(sockets);
        if(playerInRoom->GetPlayer()->IsCheating() || playerInRoom->GetPlayer()->IsDisconnected()){
            continue;
        }

        if(playerInRoom->WantsToLeave()){
            playersToLeave.push_back(playerInRoom->GetPlayer());
        }
    }

    Utils::RemoveIf(playersInRoom, [](const PlayerInRoomPtr& p){
        return p->WantsToLeave() || p->GetPlayer()->IsCheating() || p->GetPlayer()->IsDisconnected();
    });
    
    createSessions();
}

void Room::resolveSessions(fd_set* sockets){
    for(auto& session : sessions){
        session->ResolveMessage(sockets);

        if(session->IsEnded()){
            //if(!session->GetPlayer1()->GetPlayer()->IsCheating()){}
            playersInRoom.push_back(make_shared<PlayerInRoom>(session->GetPlayer1()->GetPlayer()));
            playersInRoom.push_back(make_shared<PlayerInRoom>(session->GetPlayer2()->GetPlayer()));
        }
    }

    Utils::RemoveIf(sessions, [](const SessionPtr& s){
        return s->IsEnded();
    });
}

void Room::createSessions(){
    PlayerInRoomPtr player1 = nullptr;

    for (auto& playerInRoom : playersInRoom){
        if(playerInRoom->WantsToJoinGame()){
            if(player1 != nullptr){
                sessions.push_back(make_shared<Session>(player1->GetPlayer(), playerInRoom->GetPlayer()));
                player1->SetJoiningGame();
                playerInRoom->SetJoiningGame();
                player1 = nullptr;
            }else{
                player1 = playerInRoom;
            }
        }
    }

    Utils::RemoveIf(playersInRoom, [](const PlayerInRoomPtr& p){
        return p->IsJoiningGame();
    });
}

void Room::SetPlayer(const PlayerPtr& player){
    playersInRoom.push_back(make_shared<PlayerInRoom>(player));
}

vector<PlayerPtr> Room::GetPlayersToLeave(){
    return playersToLeave;
}

vector<PlayerPtr> Room::GetPlayersToJoinGame(){
    vector<PlayerPtr> players;

    for (auto& playerInRoom : playersInRoom){
        if(playerInRoom->WantsToJoinGame()){
            players.push_back(playerInRoom->GetPlayer());
        }
    }

    return players;
}

vector<PlayerPtr> Room::GetWaitingPlayers(){
    vector<PlayerPtr> players;

    for (auto& playerInRoom : playersInRoom){
        if(!playerInRoom->WantsToJoinGame()){
            players.push_back(playerInRoom->GetPlayer());
        }
    }

    return players;
}

vector<PlayerPtr> Room::GetPlayersInSessions(){
    vector<PlayerPtr> players;

    for (auto& session : sessions){
        players.push_back(session->GetPlayer1()->GetPlayer());
        players.push_back(session->GetPlayer2()->GetPlayer());
    }

    return players;
}

vector<PlayerPtr> Room::GetPlayers(){
    vector<PlayerPtr> players;

    for(auto& player : playersToLeave){
        players.push_back(player);
    }
    for(auto& player : playersInRoom){
        players.push_back(player->GetPlayer());
    }
    for(auto& session : sessions){
        players.push_back(session->GetPlayer1()->GetPlayer());
        players.push_back(session->GetPlayer2()->GetPlayer());
    }

    return players;
}