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

        if(playerInRoom->WantsToLeave()){
            playersToLeave.push_back(new PlayerSetup(playerInRoom->GetPlayer(), PlayerSetup::CHOOSING_ROOM));
        }
    }

    Utils::RemoveIf(playersInRoom,[](PlayerInRoom* p){
        return p->WantsToLeave();
    });
}

void Room::resolveSessions(fd_set* sockets){
    for(auto& session : sessions){
        session->ResolveMessage(sockets);

        if(session->IsEnded()){
            playersInRoom.push_back(new PlayerInRoom(session->GetPlayer1()));
            playersInRoom.push_back(new PlayerInRoom(session->GetPlayer2()));
        }
    }

    Utils::RemoveIf(sessions,[](Session* s){
        return s->IsEnded();
    });
}

void Room::SetPlayer(Player* player){
    playersInRoom.push_back(new PlayerInRoom(player));
}

vector<PlayerSetup*> Room::GetPlayersToLeave(){
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
