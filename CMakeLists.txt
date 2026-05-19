cmake_minimum_required(VERSION 3.15)
project(PokerGameCPP VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

add_subdirectory(PokerGameStaticLib)
add_subdirectory(PokerServerCPP)
add_subdirectory(PokerClientCPP)