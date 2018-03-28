 
cmake_minimum_required(VERSION 2.8)

project(Game C)

add_executable(server.out bot_server.c)

add_executable(client.out client.c)
