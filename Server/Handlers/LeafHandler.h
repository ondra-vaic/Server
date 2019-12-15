//
// Created by me on 12/15/19.
//

#ifndef SERVER_LEAFHANDLER_H
#define SERVER_LEAFHANDLER_H

#include <map>
#include <functional>
#include "IMessageHandler.h"
#include "../Player.h"
#include "../Message.h"
#include "../NetworkManager.h"

using namespace std;
using namespace std::placeholders;

template <typename T, typename  S>
class LeafHandler : IMessageHandler{

protected:
    T state;
    Player* player;
    map<T, map<char, std::function<bool(Message*)>>> commands;

private:
    bool initialized;
    virtual void init() = 0;


public:
    explicit LeafHandler(Player* player){
        this->player = player;
        this->initialized = false;
    }

    void ResolveMessage(fd_set* sockets) override {

        if(!initialized){
            init();
            initialized = true;
        }

        if(!FD_ISSET(player->GetSocketId(), sockets)){
            return;
        }

        vector<string> splitMessages = NetworkManager::GetSplitMessages(player);

        if(player->IsDisconnected()){
            return;
        }

        for (const string& message : splitMessages) {
            Message* m = new Message(message, player);

            if(player->IsCheating() || player->IsDisconnected())
                return;

            if (commands.find(state) != commands.end())
            {
                if (commands[state].find(m->GetIdentifier()) != commands[state].end()) {
                    bool validFormat = commands[state][m->GetIdentifier()](m);
                    if(validFormat){
                        return;
                    }
                    cout << "incorrect identifier" << endl;
                }
                cout << "incorrect state" << endl;
            }
            //if state doesnt exist or identifier doesnt exit or is not valid format
            player->SetCheating();
        }
    }

    Player* GetPlayer(){
        return player;
    };
};


#endif //SERVER_LEAFHANDLER_H
