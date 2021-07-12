cmake_minimum_required(VERSION 3.12)
project(Kaspersky)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
add_compile_options(-pthread)

set(BUILD_SHARED_LIBS ON) # need for Boost::system
find_package(Boost 1.68 REQUIRED COMPONENTS system)

add_executable(Client
    ClientPart/clientMain.cpp
    ClientPart/Client.cpp
    ClientPart/ResultsProcessor.cpp)

add_executable(Server
    ServerPart/serverMain.cpp
    ServerPart/Server.cpp
    ServerPart/Kaspersky.cpp)
