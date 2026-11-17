file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE INC_FILES CONFIGURE_DEPENDS "include/*.h")

add_library(PokerGameStaticLib STATIC ${SRC_FILES} ${INC_FILES})


target_include_directories(PokerGameStaticLib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_include_directories(PokerGameStaticLib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/cards>
)
target_include_directories(PokerGameStaticLib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/console>
)
target_include_directories(PokerGameStaticLib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/hand>
)
target_include_directories(PokerGameStaticLib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/manager>
)
target_include_directories(PokerGameStaticLib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/player>
)
target_include_directories(PokerGameStaticLib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/server>
)

IF(WIN32)
	target_compile_definitions(PokerGameStaticLib PUBLIC _WIN32_WINNT=0x0A00)
ENDIF()

target_link_libraries(PokerGameStaticLib PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(PokerGameStaticLib PUBLIC Boost::asio)