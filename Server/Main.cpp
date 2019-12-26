#include "Server.h"

using namespace std;

#define MAX_PENDING_CONNECTIONS 10
#define MAX_NUMBER_CONNECTIONS 30
#define MAX_MESSAGE_LENGTH 255

//
//                         "0 3 0 3 0 0 0 3 "
//                         "3 0 3 0 3 0 3 0 "
//                         "0 3 0 1 0 0 0 3 "
//                         "0 0 0 0 0 0 0 0 "
//                         "0 0 0 3 0 0 0 0 "
//                         "1 0 1 0 0 0 1 0 "
//                         "0 1 0 1 0 1 0 1 "
//                         "1 0 1 0 1 0 0 0";
//


int main(int argc, char const *argv[]) {

    Server* server = new Server(10, 10, 9001, 2);
    server->MainLoop();

//
//    for(;;){
//        std::cout <<  "Listening..." << std::endl;
//
//        int player1 = accept(serverSocket, nullptr, nullptr);
//        std::cout <<  "Connected player1" << std::endl;
//        int player2 = accept(serverSocket, nullptr, nullptr);
//        std::cout <<  "Connected player2" << std::endl;
//
//        if(fork()!=0){
//            close(player1);
//            close(player2);
//        }else{
//
//            Board* board = new Board(startBoard);
//            Game* game = new Game(player1, player2, board);
//
//            board->FlipBoard();
//            NetworkManager::SendPlace(player2, board->BoardToString());
//            NetworkManager::SendMessageNumber(player2, 1);
//
//            board->FlipBoard();
//            NetworkManager::SendPlace(player1, board->BoardToString());
//            NetworkManager::SendWake(player1);
//
//            while(resolveNextMove(game)){}
//
//            close(player1);
//            close(player2);
//            return 0;
//        }
//    }

    return 0;
}






