cmake_minimum_required(VERSION 2.8)
project( regions )
set(OpenCV_DIR "/usr/local/opencv/share/OpenCV")
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( regions regions.cpp )
target_link_libraries( regions ${OpenCV_LIBS} )
