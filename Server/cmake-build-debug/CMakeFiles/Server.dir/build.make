# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/92/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/92/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/me/CLionProjects/ServerRoot/Server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/me/CLionProjects/ServerRoot/Server/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Server.dir/flags.make

CMakeFiles/Server.dir/Main.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Main.cpp.o: ../Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/me/CLionProjects/ServerRoot/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Server.dir/Main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Main.cpp.o -c /home/me/CLionProjects/ServerRoot/Server/Main.cpp

CMakeFiles/Server.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/me/CLionProjects/ServerRoot/Server/Main.cpp > CMakeFiles/Server.dir/Main.cpp.i

CMakeFiles/Server.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/me/CLionProjects/ServerRoot/Server/Main.cpp -o CMakeFiles/Server.dir/Main.cpp.s

CMakeFiles/Server.dir/Handlers/Game.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Handlers/Game.cpp.o: ../Handlers/Game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/me/CLionProjects/ServerRoot/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Server.dir/Handlers/Game.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Handlers/Game.cpp.o -c /home/me/CLionProjects/ServerRoot/Server/Handlers/Game.cpp

CMakeFiles/Server.dir/Handlers/Game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Handlers/Game.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/me/CLionProjects/ServerRoot/Server/Handlers/Game.cpp > CMakeFiles/Server.dir/Handlers/Game.cpp.i

CMakeFiles/Server.dir/Handlers/Game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Handlers/Game.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/me/CLionProjects/ServerRoot/Server/Handlers/Game.cpp -o CMakeFiles/Server.dir/Handlers/Game.cpp.s

CMakeFiles/Server.dir/Utils.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Utils.cpp.o: ../Utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/me/CLionProjects/ServerRoot/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Server.dir/Utils.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Utils.cpp.o -c /home/me/CLionProjects/ServerRoot/Server/Utils.cpp

CMakeFiles/Server.dir/Utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/me/CLionProjects/ServerRoot/Server/Utils.cpp > CMakeFiles/Server.dir/Utils.cpp.i

CMakeFiles/Server.dir/Utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/me/CLionProjects/ServerRoot/Server/Utils.cpp -o CMakeFiles/Server.dir/Utils.cpp.s

CMakeFiles/Server.dir/Board.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Board.cpp.o: ../Board.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/me/CLionProjects/ServerRoot/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Server.dir/Board.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Board.cpp.o -c /home/me/CLionProjects/ServerRoot/Server/Board.cpp

CMakeFiles/Server.dir/Board.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Board.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/me/CLionProjects/ServerRoot/Server/Board.cpp > CMakeFiles/Server.dir/Board.cpp.i

CMakeFiles/Server.dir/Board.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Board.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/me/CLionProjects/ServerRoot/Server/Board.cpp -o CMakeFiles/Server.dir/Board.cpp.s

CMakeFiles/Server.dir/NetworkManager.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/NetworkManager.cpp.o: ../NetworkManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/me/CLionProjects/ServerRoot/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Server.dir/NetworkManager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/NetworkManager.cpp.o -c /home/me/CLionProjects/ServerRoot/Server/NetworkManager.cpp

CMakeFiles/Server.dir/NetworkManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/NetworkManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/me/CLionProjects/ServerRoot/Server/NetworkManager.cpp > CMakeFiles/Server.dir/NetworkManager.cpp.i

CMakeFiles/Server.dir/NetworkManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/NetworkManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/me/CLionProjects/ServerRoot/Server/NetworkManager.cpp -o CMakeFiles/Server.dir/NetworkManager.cpp.s

CMakeFiles/Server.dir/Handlers/Session.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Handlers/Session.cpp.o: ../Handlers/Session.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/me/CLionProjects/ServerRoot/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Server.dir/Handlers/Session.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Handlers/Session.cpp.o -c /home/me/CLionProjects/ServerRoot/Server/Handlers/Session.cpp

CMakeFiles/Server.dir/Handlers/Session.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Handlers/Session.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/me/CLionProjects/ServerRoot/Server/Handlers/Session.cpp > CMakeFiles/Server.dir/Handlers/Session.cpp.i

CMakeFiles/Server.dir/Handlers/Session.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Handlers/Session.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/me/CLionProjects/ServerRoot/Server/Handlers/Session.cpp -o CMakeFiles/Server.dir/Handlers/Session.cpp.s

CMakeFiles/Server.dir/Handlers/Lobby.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Handlers/Lobby.cpp.o: ../Handlers/Lobby.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/me/CLionProjects/ServerRoot/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Server.dir/Handlers/Lobby.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Handlers/Lobby.cpp.o -c /home/me/CLionProjects/ServerRoot/Server/Handlers/Lobby.cpp

CMakeFiles/Server.dir/Handlers/Lobby.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Handlers/Lobby.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/me/CLionProjects/ServerRoot/Server/Handlers/Lobby.cpp > CMakeFiles/Server.dir/Handlers/Lobby.cpp.i

CMakeFiles/Server.dir/Handlers/Lobby.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Handlers/Lobby.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/me/CLionProjects/ServerRoot/Server/Handlers/Lobby.cpp -o CMakeFiles/Server.dir/Handlers/Lobby.cpp.s

CMakeFiles/Server.dir/Message.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Message.cpp.o: ../Message.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/me/CLionProjects/ServerRoot/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Server.dir/Message.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Message.cpp.o -c /home/me/CLionProjects/ServerRoot/Server/Message.cpp

CMakeFiles/Server.dir/Message.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Message.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/me/CLionProjects/ServerRoot/Server/Message.cpp > CMakeFiles/Server.dir/Message.cpp.i

CMakeFiles/Server.dir/Message.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Message.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/me/CLionProjects/ServerRoot/Server/Message.cpp -o CMakeFiles/Server.dir/Message.cpp.s

CMakeFiles/Server.dir/Handlers/Disconnect.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Handlers/Disconnect.cpp.o: ../Handlers/Disconnect.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/me/CLionProjects/ServerRoot/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/Server.dir/Handlers/Disconnect.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Handlers/Disconnect.cpp.o -c /home/me/CLionProjects/ServerRoot/Server/Handlers/Disconnect.cpp

CMakeFiles/Server.dir/Handlers/Disconnect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Handlers/Disconnect.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/me/CLionProjects/ServerRoot/Server/Handlers/Disconnect.cpp > CMakeFiles/Server.dir/Handlers/Disconnect.cpp.i

CMakeFiles/Server.dir/Handlers/Disconnect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Handlers/Disconnect.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/me/CLionProjects/ServerRoot/Server/Handlers/Disconnect.cpp -o CMakeFiles/Server.dir/Handlers/Disconnect.cpp.s

CMakeFiles/Server.dir/Handlers/Room.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Handlers/Room.cpp.o: ../Handlers/Room.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/me/CLionProjects/ServerRoot/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/Server.dir/Handlers/Room.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Handlers/Room.cpp.o -c /home/me/CLionProjects/ServerRoot/Server/Handlers/Room.cpp

CMakeFiles/Server.dir/Handlers/Room.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Handlers/Room.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/me/CLionProjects/ServerRoot/Server/Handlers/Room.cpp > CMakeFiles/Server.dir/Handlers/Room.cpp.i

CMakeFiles/Server.dir/Handlers/Room.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Handlers/Room.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/me/CLionProjects/ServerRoot/Server/Handlers/Room.cpp -o CMakeFiles/Server.dir/Handlers/Room.cpp.s

CMakeFiles/Server.dir/Server.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Server.cpp.o: ../Server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/me/CLionProjects/ServerRoot/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/Server.dir/Server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Server.cpp.o -c /home/me/CLionProjects/ServerRoot/Server/Server.cpp

CMakeFiles/Server.dir/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/me/CLionProjects/ServerRoot/Server/Server.cpp > CMakeFiles/Server.dir/Server.cpp.i

CMakeFiles/Server.dir/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/me/CLionProjects/ServerRoot/Server/Server.cpp -o CMakeFiles/Server.dir/Server.cpp.s

CMakeFiles/Server.dir/Handlers/PlayerSetup.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Handlers/PlayerSetup.cpp.o: ../Handlers/PlayerSetup.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/me/CLionProjects/ServerRoot/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/Server.dir/Handlers/PlayerSetup.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Handlers/PlayerSetup.cpp.o -c /home/me/CLionProjects/ServerRoot/Server/Handlers/PlayerSetup.cpp

CMakeFiles/Server.dir/Handlers/PlayerSetup.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Handlers/PlayerSetup.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/me/CLionProjects/ServerRoot/Server/Handlers/PlayerSetup.cpp > CMakeFiles/Server.dir/Handlers/PlayerSetup.cpp.i

CMakeFiles/Server.dir/Handlers/PlayerSetup.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Handlers/PlayerSetup.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/me/CLionProjects/ServerRoot/Server/Handlers/PlayerSetup.cpp -o CMakeFiles/Server.dir/Handlers/PlayerSetup.cpp.s

CMakeFiles/Server.dir/Player.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Player.cpp.o: ../Player.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/me/CLionProjects/ServerRoot/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/Server.dir/Player.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Player.cpp.o -c /home/me/CLionProjects/ServerRoot/Server/Player.cpp

CMakeFiles/Server.dir/Player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Player.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/me/CLionProjects/ServerRoot/Server/Player.cpp > CMakeFiles/Server.dir/Player.cpp.i

CMakeFiles/Server.dir/Player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Player.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/me/CLionProjects/ServerRoot/Server/Player.cpp -o CMakeFiles/Server.dir/Player.cpp.s

CMakeFiles/Server.dir/Handlers/PlayerInRoom.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Handlers/PlayerInRoom.cpp.o: ../Handlers/PlayerInRoom.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/me/CLionProjects/ServerRoot/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/Server.dir/Handlers/PlayerInRoom.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Handlers/PlayerInRoom.cpp.o -c /home/me/CLionProjects/ServerRoot/Server/Handlers/PlayerInRoom.cpp

CMakeFiles/Server.dir/Handlers/PlayerInRoom.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Handlers/PlayerInRoom.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/me/CLionProjects/ServerRoot/Server/Handlers/PlayerInRoom.cpp > CMakeFiles/Server.dir/Handlers/PlayerInRoom.cpp.i

CMakeFiles/Server.dir/Handlers/PlayerInRoom.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Handlers/PlayerInRoom.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/me/CLionProjects/ServerRoot/Server/Handlers/PlayerInRoom.cpp -o CMakeFiles/Server.dir/Handlers/PlayerInRoom.cpp.s

CMakeFiles/Server.dir/Handlers/PlayerInGame.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Handlers/PlayerInGame.cpp.o: ../Handlers/PlayerInGame.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/me/CLionProjects/ServerRoot/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/Server.dir/Handlers/PlayerInGame.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Server.dir/Handlers/PlayerInGame.cpp.o -c /home/me/CLionProjects/ServerRoot/Server/Handlers/PlayerInGame.cpp

CMakeFiles/Server.dir/Handlers/PlayerInGame.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Handlers/PlayerInGame.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/me/CLionProjects/ServerRoot/Server/Handlers/PlayerInGame.cpp > CMakeFiles/Server.dir/Handlers/PlayerInGame.cpp.i

CMakeFiles/Server.dir/Handlers/PlayerInGame.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Handlers/PlayerInGame.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/me/CLionProjects/ServerRoot/Server/Handlers/PlayerInGame.cpp -o CMakeFiles/Server.dir/Handlers/PlayerInGame.cpp.s

# Object files for target Server
Server_OBJECTS = \
"CMakeFiles/Server.dir/Main.cpp.o" \
"CMakeFiles/Server.dir/Handlers/Game.cpp.o" \
"CMakeFiles/Server.dir/Utils.cpp.o" \
"CMakeFiles/Server.dir/Board.cpp.o" \
"CMakeFiles/Server.dir/NetworkManager.cpp.o" \
"CMakeFiles/Server.dir/Handlers/Session.cpp.o" \
"CMakeFiles/Server.dir/Handlers/Lobby.cpp.o" \
"CMakeFiles/Server.dir/Message.cpp.o" \
"CMakeFiles/Server.dir/Handlers/Disconnect.cpp.o" \
"CMakeFiles/Server.dir/Handlers/Room.cpp.o" \
"CMakeFiles/Server.dir/Server.cpp.o" \
"CMakeFiles/Server.dir/Handlers/PlayerSetup.cpp.o" \
"CMakeFiles/Server.dir/Player.cpp.o" \
"CMakeFiles/Server.dir/Handlers/PlayerInRoom.cpp.o" \
"CMakeFiles/Server.dir/Handlers/PlayerInGame.cpp.o"

# External object files for target Server
Server_EXTERNAL_OBJECTS =

Server: CMakeFiles/Server.dir/Main.cpp.o
Server: CMakeFiles/Server.dir/Handlers/Game.cpp.o
Server: CMakeFiles/Server.dir/Utils.cpp.o
Server: CMakeFiles/Server.dir/Board.cpp.o
Server: CMakeFiles/Server.dir/NetworkManager.cpp.o
Server: CMakeFiles/Server.dir/Handlers/Session.cpp.o
Server: CMakeFiles/Server.dir/Handlers/Lobby.cpp.o
Server: CMakeFiles/Server.dir/Message.cpp.o
Server: CMakeFiles/Server.dir/Handlers/Disconnect.cpp.o
Server: CMakeFiles/Server.dir/Handlers/Room.cpp.o
Server: CMakeFiles/Server.dir/Server.cpp.o
Server: CMakeFiles/Server.dir/Handlers/PlayerSetup.cpp.o
Server: CMakeFiles/Server.dir/Player.cpp.o
Server: CMakeFiles/Server.dir/Handlers/PlayerInRoom.cpp.o
Server: CMakeFiles/Server.dir/Handlers/PlayerInGame.cpp.o
Server: CMakeFiles/Server.dir/build.make
Server: CMakeFiles/Server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/me/CLionProjects/ServerRoot/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking CXX executable Server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Server.dir/build: Server

.PHONY : CMakeFiles/Server.dir/build

CMakeFiles/Server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Server.dir/clean

CMakeFiles/Server.dir/depend:
	cd /home/me/CLionProjects/ServerRoot/Server/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/me/CLionProjects/ServerRoot/Server /home/me/CLionProjects/ServerRoot/Server /home/me/CLionProjects/ServerRoot/Server/cmake-build-debug /home/me/CLionProjects/ServerRoot/Server/cmake-build-debug /home/me/CLionProjects/ServerRoot/Server/cmake-build-debug/CMakeFiles/Server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Server.dir/depend

