cmake_minimum_required(VERSION 3.27)
project(ExemploPig)

add_executable(exemplo)

target_sources(exemplo
PRIVATE
    main.cpp
)

target_link_libraries(exemplo PRIVATE pig)
