cmake_minimum_required(VERSION 3.27)
project(PigDev VERSION 1.0.0)

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
add_library(pig::pig ALIAS pig)

target_sources(pig 
PUBLIC
    FILE_SET pig_headers
    TYPE HEADERS
    BASE_DIRS ./include
    FILES ${H_FILES}
PRIVATE
    ${CPP_FILES}
)

target_compile_features(pig PUBLIC cxx_std_20)

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

install(TARGETS pig
    EXPORT pigTargets
    FILE_SET pig_headers
)

install(EXPORT pigTargets
    DESTINATION share/cmake/pig
    NAMESPACE pig::
)

install(FILES ./cmake/pigConfig.cmake
    DESTINATION share/cmake/pig
)