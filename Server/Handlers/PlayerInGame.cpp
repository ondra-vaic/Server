//
// Created by me on 12/8/19.
//

#include "PlayerInGame.h"

PlayerInGame::PlayerInGame(Player* player, Game* game){

}

void PlayerInGame::ResolveMessage(){

    char identifier;
    string rawMessage;
    int messageNumber;

    if(messageNumber < this->GetCurrentMessageNumber())
        return nullptr;

    switch (identifier)
    {
        case 's':
            this->ResolvePick(rawMessage);
            return this;
        case 'm':
            this->ResolveMove(rawMessage);
            return this;
        case 'e':
            this->EndTurn();
            return this;
        case 'f':
            this->SetForfeited();
            return this;
    }


    if(IsJustWon()){
        NetworkManager::SendLoose(GetOtherPlayer());
        NetworkManager::SendWin(GetCurrentPlayer());
        return false;
    }

    if(HasForfeited()){
        NetworkManager::SendLoose(GetCurrentPlayer());
        NetworkManager::SendWin(GetOtherPlayer());
        return false;
    }

    if(HasTurnEnded()){
        Switch();

        if(!CanMove()){
            NetworkManager::SendLoose(GetCurrentPlayer());
            NetworkManager::SendWin(GetOtherPlayer());
            return false;
        }

        return true;
    }


    return true;
}
