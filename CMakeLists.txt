cmake_minimum_required(VERSION 3.21)
project(PokerGameCPP VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost CONFIG REQUIRED COMPONENTS asio)
find_package(nlohmann_json CONFIG REQUIRED)

add_subdirectory(PokerGameStaticLib)
add_subdirectory(PokerServerCPP)
add_subdirectory(PokerClientCPP)