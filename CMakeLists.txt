cmake_minimum_required(VERSION 3.13)
project(NFA)

set(CMAKE_CXX_STANDARD 14)

add_executable(NFA main.cpp Automata/NFA.cpp Automata/NFA.h Automata/State.h Automata/Transition.cpp Automata/Transition.h Automata/print.h)