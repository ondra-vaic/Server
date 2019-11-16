cmake_minimum_required(VERSION 3.15)
project(Server)

set(CMAKE_CXX_STANDARD 14)

add_executable(Server Main.cpp Game.cpp Game.h Utils.cpp Utils.h Board.cpp Board.h Vector2D.h NetworkManager.cpp NetworkManager.h)