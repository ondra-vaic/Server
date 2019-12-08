cmake_minimum_required(VERSION 3.15)
project(Server)

set(CMAKE_CXX_STANDARD 14)

add_executable(Server Main.cpp Handlers/Game.cpp Handlers/Game.h Utils.cpp Utils.h Board.cpp Board.h Vector2D.h NetworkManager.cpp NetworkManager.h Handlers/Session.cpp Handlers/Session.h Handlers/Lobby.cpp Handlers/Lobby.h Message.cpp Message.h Handlers/Disconnect.cpp Handlers/Disconnect.h Handlers/IMessageHandler.h Handlers/Room.cpp Handlers/Room.h Server.cpp Server.h Handlers/PlayerSetup.cpp Handlers/PlayerSetup.h Identifiers.h Player.cpp Player.h Handlers/PlayerInRoom.cpp Handlers/PlayerInRoom.h Handlers/PlayerInGame.cpp Handlers/PlayerInGame.h)