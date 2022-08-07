cmake_minimum_required(VERSION 3.10)

project(AngstHttpServer
    DESCRIPTION "A simple web server that supports HTTP/1.1"
    LANGUAGES CXX)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories(src)

set(SRC_DIR src)
set(TEST_DIR test)

add_executable(AngstHttpServer
    ${SRC_DIR}/http_server.cpp
    ${SRC_DIR}/http_msg.cpp
)

target_link_libraries(AngstHttpServer PRIVATE Threads::Threads)
