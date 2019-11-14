//
// Created by me on 11/5/19.
//

#include "Game.h"

Game::Game(int player1, int player2) : player1(player1), player2(player2), player1Turn(true){}

int Game::GetCurrentPlayer() {
    return player1Turn ? player1 : player2;
}

int Game::GetOtherPlayer() {
    return player1Turn ?  player2 : player1;
}

void Game::SetPlayer1Turn(){
    player1Turn = true;
}