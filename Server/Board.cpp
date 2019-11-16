//
// Created by me on 11/15/19.
//

#include "Board.h"
#include "Utils.h"

#define BOARD_DIMENSION 8
Board::Board(int** board): board(board){}

Board::Board(const string& board){
    this->board = stringToBoard(board);
}



string Board::BoardToString(){
    string boardString;
    for (int i = 0; i < BOARD_DIMENSION; ++i) {
        for (int j = 0; j < BOARD_DIMENSION; ++j) {
            if(!(i == 0 && j == 0))
            {
                boardString += " ";
            }
            boardString += to_string(board[j][i]);
        }
    }
    return boardString;
}

int** Board::stringToBoard(const string& boardString){

    int** board = initializeBoardArray();

    for (int i = 0; i < boardString.size(); i+=2)
    {
        int side = boardString[i] - '0';

        if (side == 0)
        {
            continue;
        }

        int x = (i / 2) % BOARD_DIMENSION;
        int y = (i / 2) / BOARD_DIMENSION;

        board[x][y] = side;
    }

    return board;
}

void Board::FlipBoard(){
    int** flippedBoard = initializeBoardArray();

    for (int i = 0; i < BOARD_DIMENSION; ++i) {
        for (int j = 0; j < BOARD_DIMENSION; ++j) {

            int figureType = board[i][BOARD_DIMENSION - j - 1];
            if(figureType != 0){
                figureType = 4 - figureType;
            }
            flippedBoard[i][j] = figureType;
        }
    }
    board = flippedBoard;
}

int Board::GetFigurine(int x, int y){
    if(!Utils::IsInPlayingField(x, y))
    {
        return -1;
    }

    return board[x][y];
}

void Board::SetFigure(int figurine, int x, int y){
    board[x][y] = figurine;
}



int** Board::initializeBoardArray(){
    int** board = new int*[BOARD_DIMENSION];

    for (int i = 0; i < BOARD_DIMENSION; ++i) {
        board[i] = new int[BOARD_DIMENSION];
    }
    return board;
}