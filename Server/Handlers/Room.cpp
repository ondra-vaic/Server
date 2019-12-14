//
// Created by me on 12/6/19.
//

#include <algorithm>
#include "Room.h"
#include "../Utils.h"

void Room::ResolveMessage(fd_set* sockets){
    resolvePlayersInRoom(sockets);
    resolveSessions(sockets);
}

void Room::resolvePlayersInRoom(fd_set* sockets){
    playersToLeave.clear();

    for(auto& playerInRoom : playersInRoom){
        playerInRoom->ResolveMessage(sockets);

        if(playerInRoom->WantsToLeave() || playerInRoom->GetPlayer()->IsCheating() || playerInRoom->GetPlayer()->IsDisconnected()){
            playersToLeave.push_back(playerInRoom->GetPlayer());
            //TODO FREE PLAYERINROOM
        }
    }

    Utils::RemoveIf(playersInRoom, [](PlayerInRoom* p){
        return p->WantsToLeave();
    });
}

void Room::resolveSessions(fd_set* sockets){
    for(auto& session : sessions){
        session->ResolveMessage(sockets);

        if(session->IsEnded()){
            playersInRoom.push_back(new PlayerInRoom(session->GetPlayer1()->GetPlayer()));
            playersInRoom.push_back(new PlayerInRoom(session->GetPlayer2()->GetPlayer()));
        }
    }

    Utils::RemoveIf(sessions,[](Session* s){
        return s->IsEnded();
    });
}

void Room::SetPlayer(Player* player){
    playersInRoom.push_back(new PlayerInRoom(player));
}

vector<Player*> Room::GetPlayersToLeave(){
    return playersToLeave;
}

void Room::CreateSessions(){
    PlayerInRoom* player1 = nullptr;

    for (auto& playerInRoom : playersInRoom){
        if(playerInRoom->WantsToJoinGame()){
            if(player1  != nullptr){
                sessions.push_back(new Session(player1->GetPlayer(), playerInRoom->GetPlayer()));
                player1->SetJoiningGame();
                playerInRoom->SetJoiningGame();
                player1 = nullptr;
            }else{
                player1 = playerInRoom;
            }
        }
    }

    Utils::RemoveIf(playersInRoom, [](PlayerInRoom* p){
        return p->IsJoiningGame();
    });
}

vector<Player*> Room::GetPlayers(){
    vector<Player*> players;

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