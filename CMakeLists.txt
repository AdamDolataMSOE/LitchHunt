cmake_minimum_required(VERSION 3.26)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)

# Add executable
add_executable(src
        litch_hunt.cpp
        hazards.cpp
        map_parts.cpp
        player_character.cpp
        )