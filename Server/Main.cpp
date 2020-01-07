#include "Server.h"

#include <fstream>
#include <string>

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

    int maxPlayers = -1;
    int maxPendingConnections = -1;
    int port = -1;
    int numberOfRooms = -1;

    ifstream config;
    config.open("ServerConfig.con", ios::in);

    string line;
    while (getline(config, line))
    {
        istringstream iss(line);
        int val;
        string key;
        if (!(iss >> key >> val) || val < 0) {
            cout << "Error processing config file, make sure all values are set, all values are positive and the format is correct" <<endl;
            return 1;
        }

        if(key == "maxNumPlayers"){
            maxPlayers = val;
        }else if(key == "maxPendingConnections"){
            maxPendingConnections = val;
        }else if(key == "port"){
            port = val;
        }else if(key == "numberOfRooms"){
            numberOfRooms = val;
        }

        cout << key << " " << val << endl;
    }
    if(maxPlayers == -1 || maxPendingConnections == -1 || port == -1, numberOfRooms == -1){
        cout << "Error processing config file, make sure all values are set, all values are positive and the format is correct" <<endl;
        return 1;
    }

    Server* server = new Server(maxPlayers, maxPendingConnections, port, numberOfRooms);
    server->MainLoop();

    return 0;
}






