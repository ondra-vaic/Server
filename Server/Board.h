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
    static int** stringToBoard(const string& boardString);
    static int** initializeBoardArray();
    
public:
    explicit Board(const string &board);
    explicit Board(int **board);

    string BoardToString();
    void FlipBoard();
    int GetFigurine(int x, int y);
    void SetFigure(int figurine, int x, int y);
};


#endif //SERVER_BOARD_H
