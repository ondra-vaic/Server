//
// Created by me on 12/7/19.
//

#include <iostream>
#include <unistd.h>
#include "Player.h"
#include "Utils.h"

#define TIME_TO_DC 30

Player::Player(int socketId){
    this->socketId = socketId;
    this->disconnected = false;
    this->cheating = false;
    this->room = -1;
    this->sessionId = -1;
    this->read = false;
    this->lastPingTime = INT_MAX;
}

int Player::GetSocketId(){
    return socketId;
}

void Player::SetRead(bool read){
    this->read = read;
}

bool Player::IsRead(){
    return read;
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
    cout << "Disconnect " << name << " " << GetSocketId() << endl;
    close(GetSocketId());
    socketId = -1;
    this->disconnected = true;
}

void Player::SetRoom(int room){
    this->room = room;
}

void Player::SetName(const string& name){
    this->name = name;
}

void Player::SetSocketId(int socketId){
    this->socketId = socketId;
}

void Player::SetSessionId(int sessionId){
    this->sessionId = sessionId;
}

void Player::ResetErrors(){
    disconnected = false;
    cheating = false;
    lastPingTime = Utils::GetCurrentTime();
}

void Player::SetCheating(){
    cout << "Cheatin " << name << " " << GetSocketId() << endl;
    close(GetSocketId());
    socketId = -1;
    this->cheating = true;
}

void Player::Ping(){
    lastPingTime = Utils::GetCurrentTime();
    cout << "++++++ pinged +++++++" <<endl;
}

void Player::CheckDisconnected(){
    if(Utils::GetCurrentTime() - lastPingTime > TIME_TO_DC){

        cout << "---------- time out ---------" << endl;
        SetDisconnected();
    }
}