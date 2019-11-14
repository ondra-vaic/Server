//
// Created by me on 11/5/19.
//

#ifndef SERVER_GAME_H
#define SERVER_GAME_H


class Game {

private:
    int player1;
    int player2;
    bool player1Turn;

public:
    Game(int player1, int player2);
    int GetCurrentPlayer();
    int GetOtherPlayer();
    void SetPlayer1Turn();

};


#endif //SERVER_GAME_H
