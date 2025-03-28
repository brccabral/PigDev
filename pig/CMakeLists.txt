cmake_minimum_required(VERSION 3.27)
project(PigDev VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# install SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_net REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_ttf REQUIRED)
# install ffmpeg
find_library(LIBAVCODEC avcodec REQUIRED)
find_library(LIBAVDEVICE avdevice REQUIRED)
find_library(LIBAVFILTER avfilter REQUIRED)
find_library(LIBAVFORMAT avformat REQUIRED)
find_library(LIBAVUTIL avutil REQUIRED)
find_library(LIBSWRESAMPLE swresample REQUIRED)
find_library(LIBSWSCALE swscale REQUIRED)

file(GLOB CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB H_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/pig/*.h")

add_library(pig STATIC)

target_sources(pig 
PUBLIC
    FILE_SET pig_headers
    TYPE HEADERS
    BASE_DIRS ./include
    FILES ${H_FILES}
PRIVATE
    ${CPP_FILES}
)

target_compile_definitions(pig PUBLIC
        PIGCOMAUDIO
        PIGCOMREDE
        PIGCOMCONTROLE
        PIGCOMFORM
        PIGCOMTELA
        PIGCOMVIDEO
)
target_compile_options(pig PRIVATE "-march=native")
target_link_libraries(pig PUBLIC
        ${SDL2_LIBRARIES}
        SDL2_net
        SDL2_image
        SDL2_mixer
        SDL2_ttf
)
target_link_libraries(pig PUBLIC
    avcodec
    avdevice
    avfilter
    avformat
    avutil
    swresample
    swscale
)
add_custom_command(TARGET pig POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
