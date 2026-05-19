file(GLOB_RECURSE SRC_FILES "src/*.cpp")
file(GLOB_RECURSE INC_FILES "include/*.h")

add_executable(PokerClientCPP ${SRC_FILES} ${INC_FILES})

target_include_directories(PokerClientCPP PRIVATE include)

target_link_libraries(PokerClientCPP PRIVATE PokerGameStaticLib)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/data" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")