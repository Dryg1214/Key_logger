cmake_minimum_required(VERSION 3.0)
project(key_logger)


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
link_libraries( Threads::Threads rt atomic)

add_executable(key_logger main.cpp GetProcessesList.cpp Mice.h write_asynk.cpp)
target_link_libraries(key_logger X11 Xi)