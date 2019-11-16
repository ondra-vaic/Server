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
    int GetFigure(int x, int y);
    void SetFigure(int figurine, int x, int y);
    bool IsFigurine(int figurine);
    bool IsKing(int figurine);
    bool IsPlayer1(int figurine);
};


#endif //SERVER_BOARD_H
