//
// Created by me on 12/15/19.
//

#ifndef SERVER_LEAFHANDLER_H
#define SERVER_LEAFHANDLER_H

#include <map>
#include <functional>
#include <memory>
#include "IMessageHandler.h"
#include "../Player.h"
#include "../Message.h"
#include "../NetworkManager.h"
#include "../Identifiers.h"

using namespace std;
using namespace std::placeholders;

template <typename T, typename  S>
class LeafHandler : IMessageHandler{

protected:
    T state;
    PlayerPtr player;
    map<T, map<char, std::function<bool(MessagePtr)>>> commands;

private:
    bool initialized;
    virtual void init() = 0;


public:
    explicit LeafHandler(const PlayerPtr& player) : player(player){
        this->initialized = false;
    }

    void ResolveMessage(fd_set* sockets) override {

        if(!initialized){
            init();
            initialized = true;
        }

        if(!FD_ISSET(player->GetSocketId(), sockets) || player->IsRead()){
            return;
        }
        NetworkManager::GetResponse(player);
        player->CreateMessages();

        vector<string> splitMessages = player->GetReadyMessages();
        player->SetRead(true);

        if(player->IsDisconnected()){
            return;
        }

        for (const string& message : splitMessages) {
            MessagePtr m = make_shared<Message>(message, player);

            if(m->GetIdentifier() == PING){
                player->Ping();
                NetworkManager::SendConfirm(player, m->GetMessageNumber());
                continue;
            }

            if(player->IsCheating() || player->IsDisconnected())
                return;

            if (commands.find(state) != commands.end())
            {
                if (commands[state].find(m->GetIdentifier()) != commands[state].end()) {
                    bool validFormat = commands[state][m->GetIdentifier()](m);

                    if(validFormat){
                        NetworkManager::SendConfirm(player, m->GetMessageNumber());
                        continue;
                    }
                    cout << " invalid format or information " << endl;
                }
                cout << "incorrect identifier" << endl;
            }
            cout << "incorrect state" << endl;

            //if state doesnt exist or identifier doesnt exit or is not valid format
            player->SetCheating();
            return;
        }
        player->ClearReadyMessages();
    }

    PlayerPtr GetPlayer(){
        return player;
    };
};


#endif //SERVER_LEAFHANDLER_H
