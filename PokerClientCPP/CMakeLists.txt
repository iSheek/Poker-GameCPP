file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE INC_FILES CONFIGURE_DEPENDS "include/*.h")

add_executable(PokerClientCPP ${SRC_FILES} ${INC_FILES})

target_include_directories(PokerClientCPP PRIVATE include)

target_link_libraries(PokerClientCPP PRIVATE PokerGameStaticLib)

add_custom_command(TARGET PokerClientCPP POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/data" "$<TARGET_FILE_DIR:PokerClientCPP>/data")