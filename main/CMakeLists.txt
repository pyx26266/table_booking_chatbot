
cmake_minimum_required(VERSION 2.8)

project(ChatBot C)

INCLUDE_DIRECTORIES (${CMAKE_SOURCE_DIR})

add_executable(${PROJECT_NAME} bot_server.c)

target_link_libraries(${PROJECT_NAME} basic_socket_functions record_list)

add_executable(client client.c)

target_link_libraries(client basic_socket_functions record_list)
