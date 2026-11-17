file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp" "tests/src/*.cpp")
file(GLOB_RECURSE INC_FILES CONFIGURE_DEPENDS "include/*.h" "tests/include/*.h")

add_executable(PokerServerCPP ${SRC_FILES} ${INC_FILES})

target_include_directories(PokerServerCPP PRIVATE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tests/include>
)
target_link_libraries(PokerServerCPP PRIVATE PokerGameStaticLib)