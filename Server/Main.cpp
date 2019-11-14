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

#include "Game.h"

#define MAX_PENDING_CONNECTIONS 10
#define MAX_NUMBER_CONNECTIONS 30
#define MAX_MESSAGE_LENGTH 255

const char* startBoard = "p"
                         "0 3 0 3 0 3 0 3 "
                         "3 0 3 0 3 0 3 0 "
                         "0 3 0 3 0 3 0 3 "
                         "0 0 0 0 0 0 0 0 "
                         "0 0 0 0 0 0 0 0 "
                         "1 0 1 0 1 0 1 0 "
                         "0 1 0 1 0 1 0 1 "
                         "1 0 1 0 1 0 1 0";

int serverSocket;
void error(const char *msg){
    perror(msg);
    exit(1);
}

void setUp(){
    //socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    //server adress
    struct sockaddr_in serverAdress;
    serverAdress.sin_family = AF_INET;
    serverAdress.sin_port = htons(9002);
    serverAdress.sin_addr.s_addr =  INADDR_ANY;

    //bind socket
    bind(serverSocket, (struct sockaddr*) &serverAdress, sizeof(serverAdress));
}

char* getResponse(int clientId){
    char* response = new char[255];
    recv(clientId, response, sizeof(response), 0);
    printf("Recieved -[%s]- from %d\n", response, clientId);

    return response;
}

bool validateMove(char* move){
    return true;
}

void sendMessage(int clientId, const char* message){

    char *completeMessage = new char[255];

    strcpy(completeMessage, message);
    strcat(completeMessage, "|");

    send(clientId, completeMessage, strlen(completeMessage), 0);
    printf("Sent -[%s]- to %d\n", completeMessage, clientId);
}


int resolveNextMove(Game* game){

    char* message = getResponse(game->GetCurrentPlayer());

    if(validateMove(message)){
        sendMessage(game->GetOtherPlayer(), message);
    }else{
        error("Invalid Move");
    }

    return 0;
}

int main(int argc, char const *argv[])
{
    std::cout <<  "Server up" << std::endl;

    setUp();
    std::cout <<  "Server is set up" << std::endl;

    listen(serverSocket, MAX_PENDING_CONNECTIONS);

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

            Game* game = new Game(player1, player2);

            sendMessage(player1, startBoard);
            sendMessage(player2, startBoard);
            sendMessage(player1, "w");

            while(true){
                resolveNextMove(game);
            }
        }
    }


    close(serverSocket);
    return 0;





    /*
    //int player2 = accept(serverSocket, nullptr, nullptr);

    //Game* game = new Game(player1, player2);

    sendMessage(player1, startBoard);
    //sendMessage(player2, startBoard);
    sendMessage(player1, "w");



    */

    close(serverSocket);
    return 0;
}
























