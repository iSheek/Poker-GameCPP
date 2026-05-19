file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable(PokerServerCPP ${SRC_FILES})


target_link_libraries(PokerServerCPP PRIVATE PokerGameStaticLib)