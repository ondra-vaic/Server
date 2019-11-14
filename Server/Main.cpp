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
using namespace std;

#define MAX_PENDING_CONNECTIONS 10
#define MAX_NUMBER_CONNECTIONS 30
#define MAX_MESSAGE_LENGTH 255

const string startBoard =
                         "0 3 0 3 0 3 0 3 "
                         "3 0 3 0 3 0 3 0 "
                         "0 3 0 3 0 3 0 3 "
                         "0 0 0 0 0 0 0 0 "
                         "0 0 0 0 0 0 0 0 "
                         "1 0 1 0 1 0 1 0 "
                         "0 1 0 1 0 1 0 1 "
                         "1 0 1 0 1 0 1 0";

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

string getResponse(int clientId){
    char* response = new char[MAX_MESSAGE_LENGTH];
    recv(clientId, response, sizeof(response), 0);
    printf("Recieved -[%s]- from %d\n", response, clientId);

    string reponseString(response);
    return reponseString;
}

void sendMessage(int clientId, const string& identifier, const string& message){

    string completeMessage = identifier + message + "|";
    send(clientId, completeMessage.c_str(), completeMessage.length(), 0);\

    cout << "Sent [" << completeMessage << "]" << "to " << clientId << endl;
}

char getIdentifier(string message){
    return message[0];
}

string getRawMessage(const string& message){
    return message.substr(1, message.size());
}

void resolveMessage(const string& message){

    char identifier = getIdentifier(message);
    string rawMessage = getRawMessage(message);
    cout << rawMessage << " " << identifier;
//
//    switch (identifier)
//    {
//        case 'd':
//            resolveDelete(rawMessage);
//            break;
//        case 'm':
//            resolveMove(rawMessage);
//            break;
//        case 'w':
//            //gameManager.SetTurn();
//            break;
//        case 'p':
//            resolvePlace(rawMessage);
//            break;
//    }
//
//    if(validateMove(message)){
//        sendMessage(game->GetOtherPlayer(), message);
//    }else{
//        printf("Invalid Move");
//    }
}


vector<string> getSplitMessages(string messages){
    vector<string> splitMessages;

    size_t position = 0;
    string message;
    while ((position = messages.find('|')) != string::npos) {
        message = messages.substr(0, position);
        splitMessages.push_back(message);
        messages.erase(0, position + 1);
    }

    //splitMessages.pop_back();

    return splitMessages;
}


int resolveNextMove(Game* game){

    vector<string> splitMessages = getSplitMessages(getResponse(game->GetCurrentPlayer()));
    for (const string& message : splitMessages) {
        resolveMessage(message);
    }

    return 0;
}


int main(int argc, char const *argv[])
{
    std::cout <<  "Server up" << std::endl;
    setUp();

    Board board(startBoard);
    board.FlipBoard();

    cout << board.BoardToString();

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



            sendMessage(player1, "p", startBoard);
            sendMessage(player2, "p", board.BoardToString());
            sendMessage(player1, "w", "");

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



