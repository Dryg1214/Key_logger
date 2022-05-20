cmake_minimum_required(VERSION 3.0)
project(key_logger)
add_executable(key_logger main.cpp GetProcessesList.cpp Mice.h write_asynk.cpp)
target_link_libraries(key_logger X11 Xi)