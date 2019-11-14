//
// Created by me on 11/15/19.
//

#ifndef SERVER_BOARD_H
#define SERVER_BOARD_H
#include <string>
#include <iostream>
using namespace std;

class Board {


private:
    int** board;
    int** stringToBoard(const string& boardString);
    static int** initializeBoardArray();

    int** flipBoard(int** board);

public:
    Board(const string& board);
    Board(int** board);
    string BoardToString();
    void FlipBoard();

};


#endif //SERVER_BOARD_H
