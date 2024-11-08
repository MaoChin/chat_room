# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/luckydog/project/chat_room/server_code/chat_server/voice

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/luckydog/project/chat_room/server_code/chat_server/voice/build

# Include any dependencies generated for this target.
include CMakeFiles/voice_client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/voice_client.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/voice_client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/voice_client.dir/flags.make

voice_recognition.pb.cc: /home/luckydog/project/chat_room/server_code/chat_server/proto/voice_recognition.proto
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/luckydog/project/chat_room/server_code/chat_server/voice/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) /home/luckydog/project/chat_room/server_code/chat_server/voice/build/voice_recognition.pb.cc
	protoc --cpp_out=/home/luckydog/project/chat_room/server_code/chat_server/voice/build -I /home/luckydog/project/chat_room/server_code/chat_server/voice/../proto --experimental_allow_proto3_optional /home/luckydog/project/chat_room/server_code/chat_server/voice/../proto/voice_recognition.proto

CMakeFiles/voice_client.dir/test/voiceClient.cc.o: CMakeFiles/voice_client.dir/flags.make
CMakeFiles/voice_client.dir/test/voiceClient.cc.o: ../test/voiceClient.cc
CMakeFiles/voice_client.dir/test/voiceClient.cc.o: CMakeFiles/voice_client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luckydog/project/chat_room/server_code/chat_server/voice/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/voice_client.dir/test/voiceClient.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/voice_client.dir/test/voiceClient.cc.o -MF CMakeFiles/voice_client.dir/test/voiceClient.cc.o.d -o CMakeFiles/voice_client.dir/test/voiceClient.cc.o -c /home/luckydog/project/chat_room/server_code/chat_server/voice/test/voiceClient.cc

CMakeFiles/voice_client.dir/test/voiceClient.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voice_client.dir/test/voiceClient.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luckydog/project/chat_room/server_code/chat_server/voice/test/voiceClient.cc > CMakeFiles/voice_client.dir/test/voiceClient.cc.i

CMakeFiles/voice_client.dir/test/voiceClient.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voice_client.dir/test/voiceClient.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luckydog/project/chat_room/server_code/chat_server/voice/test/voiceClient.cc -o CMakeFiles/voice_client.dir/test/voiceClient.cc.s

CMakeFiles/voice_client.dir/voice_recognition.pb.cc.o: CMakeFiles/voice_client.dir/flags.make
CMakeFiles/voice_client.dir/voice_recognition.pb.cc.o: voice_recognition.pb.cc
CMakeFiles/voice_client.dir/voice_recognition.pb.cc.o: CMakeFiles/voice_client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luckydog/project/chat_room/server_code/chat_server/voice/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/voice_client.dir/voice_recognition.pb.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/voice_client.dir/voice_recognition.pb.cc.o -MF CMakeFiles/voice_client.dir/voice_recognition.pb.cc.o.d -o CMakeFiles/voice_client.dir/voice_recognition.pb.cc.o -c /home/luckydog/project/chat_room/server_code/chat_server/voice/build/voice_recognition.pb.cc

CMakeFiles/voice_client.dir/voice_recognition.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/voice_client.dir/voice_recognition.pb.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luckydog/project/chat_room/server_code/chat_server/voice/build/voice_recognition.pb.cc > CMakeFiles/voice_client.dir/voice_recognition.pb.cc.i

CMakeFiles/voice_client.dir/voice_recognition.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/voice_client.dir/voice_recognition.pb.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luckydog/project/chat_room/server_code/chat_server/voice/build/voice_recognition.pb.cc -o CMakeFiles/voice_client.dir/voice_recognition.pb.cc.s

# Object files for target voice_client
voice_client_OBJECTS = \
"CMakeFiles/voice_client.dir/test/voiceClient.cc.o" \
"CMakeFiles/voice_client.dir/voice_recognition.pb.cc.o"

# External object files for target voice_client
voice_client_EXTERNAL_OBJECTS =

voice_client: CMakeFiles/voice_client.dir/test/voiceClient.cc.o
voice_client: CMakeFiles/voice_client.dir/voice_recognition.pb.cc.o
voice_client: CMakeFiles/voice_client.dir/build.make
voice_client: /usr/lib/x86_64-linux-gnu/libjsoncpp.so.19
voice_client: CMakeFiles/voice_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/luckydog/project/chat_room/server_code/chat_server/voice/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable voice_client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/voice_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/voice_client.dir/build: voice_client
.PHONY : CMakeFiles/voice_client.dir/build

CMakeFiles/voice_client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/voice_client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/voice_client.dir/clean

CMakeFiles/voice_client.dir/depend: voice_recognition.pb.cc
	cd /home/luckydog/project/chat_room/server_code/chat_server/voice/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/luckydog/project/chat_room/server_code/chat_server/voice /home/luckydog/project/chat_room/server_code/chat_server/voice /home/luckydog/project/chat_room/server_code/chat_server/voice/build /home/luckydog/project/chat_room/server_code/chat_server/voice/build /home/luckydog/project/chat_room/server_code/chat_server/voice/build/CMakeFiles/voice_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/voice_client.dir/depend

