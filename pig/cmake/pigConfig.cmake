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

include("${CMAKE_CURRENT_LIST_DIR}/pigTargets.cmake")
