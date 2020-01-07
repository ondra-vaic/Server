//
// Created by me on 11/15/19.
//

#include <algorithm>
#include "Board.h"
#include "Utils.h"

const string startBoard =
        "0 0 0 0 0 0 0 0 "
        "0 0 0 0 0 0 0 0 "
        "0 0 0 0 3 0 0 0 "
        "0 0 0 0 0 0 0 0 "
        "0 0 0 0 0 0 0 0 "
        "0 1 0 1 0 1 0 1 "
        "1 0 1 0 3 0 1 0 "
        "0 1 0 1 0 0 0 1 ";
//
//const string startBoard =
//        "3 0 3 0 3 0 3 0 "
//        "0 3 0 3 0 3 0 3 "
//        "3 0 3 0 3 0 3 0 "
//        "0 0 0 0 0 0 0 0 "
//        "0 0 0 0 0 0 0 0 "
//        "0 1 0 1 0 1 0 1 "
//        "1 0 1 0 1 0 1 0 "
//        "0 1 0 1 0 1 0 1 ";

#define BOARD_DIMENSION 8
Board::Board(int** board): board(board){}

Board::Board(const string& board){
    this->board = stringToBoard(board);
}

Board::Board(){
    this->board = stringToBoard(startBoard);
}

string Board::BoardToString(){
    string boardString;
    for (int j = 0; j < BOARD_DIMENSION; ++j) {
        for (int i = 0; i < BOARD_DIMENSION; ++i) {
            if(!(i == 0 && j == 0))
            {
                boardString += " ";
            }
            boardString += to_string(board[i][BOARD_DIMENSION - 1 - j]);
        }
    }
    return boardString;
}

int** Board::stringToBoard(const string& boardString){

    int** board = initializeBoardArray();

    for (int i = 0; i < boardString.size(); i+=2)
    {
        int side = boardString[i] - '0';

        int x = (i / 2) % BOARD_DIMENSION;
        int y = BOARD_DIMENSION - 1 - (i / 2) / BOARD_DIMENSION;

        board[x][y] = side;
    }

    return board;
}

void Board::FlipBoard(){
    int** flippedBoard = initializeBoardArray();

    for (int j = 0; j < BOARD_DIMENSION; ++j) {
        for (int i = 0; i < BOARD_DIMENSION; ++i) {
            int figurineType = board[i][BOARD_DIMENSION - 1 - j];
            flippedBoard[i][j] = Utils::InvertFigurineType(figurineType);
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

bool Board::IsWin(){
    for (int i = 0; i < BOARD_DIMENSION; ++i) {
        for (int j = 0; j < BOARD_DIMENSION; ++j) {
            if(Utils::IsEnemy(board[i][j]))
                return false;
        }
    }
    return true;
}

