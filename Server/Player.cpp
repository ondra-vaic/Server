//
// Created by me on 12/7/19.
//

#include "Player.h"


Player::Player(int socketId){
    this->socketId = socketId;
}

int Player::GetSocketId(){
    return socketId;
}

int Player::GetRoom(){
    return room;
}

string Player::GetName(){
    return name;
}

int Player::GetSessionId(){
    return sessionId;
}

bool Player::IsCheating(){
    return cheating;
}

bool Player::IsDisconnected(){
    return disconnected;
}

void Player::SetDisconnected(){
    this->disconnected = true;
}

void Player::SetRoom(int room){
    this->room = room;
}

void Player::SetSessionId(int sessionId){
    this->sessionId = sessionId;
}

void Player::SetCheating(){
    this->cheating = true;
}