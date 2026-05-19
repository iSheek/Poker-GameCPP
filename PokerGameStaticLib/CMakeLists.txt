file(GLOB_RECURSE SRC_FILES "src/*.cpp")
file(GLOB_RECURSE INC_FILES "include/*.h")

add_library(PokerGameStaticLib STATIC ${SRC_FILES} ${INC_FILES})


target_include_directories(PokerGameStaticLib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(PokerGameStaticLib PUBLIC nlohmann_json::nlohmann_json)