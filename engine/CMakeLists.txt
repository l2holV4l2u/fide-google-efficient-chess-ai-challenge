cmake_minimum_required(VERSION 3.10)
project(ChessEngine)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Source files
set(SOURCES
    chess.cpp
    main.cpp
    movegen.cpp
    movepick.cpp
)

# Include header files directory (if needed)
include_directories(${CMAKE_SOURCE_DIR})

# Create the executable
add_executable(chess_engine ${SOURCES})