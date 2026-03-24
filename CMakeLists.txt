cmake_minimum_required(VERSION 3.30)
project(Project1)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")

add_executable(Project1 main.cpp
        Komiwojadzer/BruteForce.cpp
        Komiwojadzer/BruteForce.h
        Komiwojadzer/NearestNeighbor.cpp
        Komiwojadzer/NearestNeighbor.h
        Komiwojadzer/RepetitiveNearestNeighbour.cpp
        Komiwojadzer/RepetitiveNearestNeighbour.h
        Komiwojadzer/Random.cpp
        Komiwojadzer/Random.h
        Komiwojadzer/Results.cpp
        Komiwojadzer/Results.h
        Komiwojadzer/Timer.cpp
        Komiwojadzer/Timer.h
)
