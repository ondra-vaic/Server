cmake_minimum_required(VERSION 3.15)
project(Server)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread" )

add_executable(Server Main.cpp Game.cpp Game.h Utils.cpp Utils.h Board.cpp Board.h Vector2D.h NetworkManager.cpp NetworkManager.h Handlers/Session.cpp Handlers/Session.h Message.cpp Message.h Handlers/IMessageHandler.h Handlers/Room.cpp Handlers/Room.h Server.cpp Server.h Handlers/PlayerSetup.cpp Handlers/PlayerSetup.h Identifiers.h Player.cpp Player.h Handlers/PlayerInRoom.cpp Handlers/PlayerInRoom.h Handlers/PlayerInGame.cpp Handlers/PlayerInGame.h Handlers/LeafHandler.cpp Handlers/LeafHandler.h)