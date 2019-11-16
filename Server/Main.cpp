#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include<vector>
#include <sstream>
#include "Game.h"
#include "Board.h"
#include "NetworkManager.h"

using namespace std;

#define MAX_PENDING_CONNECTIONS 10
#define MAX_NUMBER_CONNECTIONS 30
#define MAX_MESSAGE_LENGTH 255

const string startBoard =
                         "0 3 0 3 0 3 0 3 "
                         "3 0 3 0 3 0 3 0 "
                         "0 3 0 3 0 3 0 3 "
                         "0 0 0 0 0 0 0 0 "
                         "0 0 0 3 0 0 0 0 "
                         "1 0 1 0 0 0 1 0 "
                         "0 1 0 1 0 1 0 1 "
                         "1 0 1 0 1 0 0 0";

int serverSocket;
void error(int code, const char *msg){
    if(code != 0){
        perror(msg);
        exit(1);
    }
}

void setUp() {

    int return_value;
    int param = 1;

    //socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    return_value = setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (const char *) &param, sizeof(int));
    error(return_value, "Setsockopt Error");

    //server adress
    struct sockaddr_in serverAdress;
    serverAdress.sin_family = AF_INET;
    serverAdress.sin_port = htons(9002);
    serverAdress.sin_addr.s_addr = INADDR_ANY;

    //bind socket
    return_value = bind(serverSocket, (struct sockaddr *) &serverAdress, sizeof(serverAdress));
    error(return_value, "Bind Error");

    //listen
    return_value = listen(serverSocket, MAX_PENDING_CONNECTIONS);
    error(return_value, "Listen Error");
}

bool resolveMessage(Game* game, const string& message){

    char identifier = NetworkManager::GetIdentifier(message);
    string rawMessage = NetworkManager::GetRawMessage(message);
   // cout << rawMessage << " " << identifier;

    switch (identifier)
    {
        case 's':
            game->ResolvePick(rawMessage);
            break;
        case 'm':
            game->ResolveMove(rawMessage);
            break;
//        case 'p':
//            resolvePlace(rawMessage);
//            break;
    }

//
//    if(validateMove(message)){
//        sendMessage(game->GetOtherPlayer(), message);
//    }else{
//        printf("Invalid Move");
//    }

    return false;
}

void resolveNextMove(Game* game){
    vector<string> splitMessages = NetworkManager::GetSplitMessages(NetworkManager::GetResponse(game->GetCurrentPlayer()));

    for (const string& message : splitMessages) {
        resolveMessage(game, message);
        if(game->TurnHasEnded()){
            game->Switch();
            break;
        }
    }
}


int main(int argc, char const *argv[])
{
    std::cout <<  "Server up" << std::endl;
    setUp();

    for(;;){
        std::cout <<  "Listening..." << std::endl;

        int player1 = accept(serverSocket, nullptr, nullptr);
        std::cout <<  "Connected player1" << std::endl;
        int player2 = accept(serverSocket, nullptr, nullptr);
        std::cout <<  "Connected player2" << std::endl;

        if(fork()!=0){
            close(player1);
            close(player2);
        }else{

            Board* board = new Board(startBoard);
            Game* game = new Game(player1, player2, board);

            board->FlipBoard();
            NetworkManager::SendPlace(player2, board->BoardToString());

            board->FlipBoard();
            NetworkManager::SendPlace(player1, board->BoardToString());
            NetworkManager::SendWake(player1);

            while(true){
                resolveNextMove(game);
            }
        }
    }


    close(serverSocket);
    return 0;
}



