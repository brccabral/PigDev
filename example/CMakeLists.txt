cmake_minimum_required(VERSION 3.27)
project(ExemploPig)

find_package(pig REQUIRED)

add_executable(exemplo)

target_sources(exemplo
PRIVATE
    main.cpp
)

target_link_libraries(exemplo PRIVATE pig::pig)

add_custom_command(TARGET exemplo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)

install(TARGETS exemplo)

install(DIRECTORY ./assets
    DESTINATION bin
)
