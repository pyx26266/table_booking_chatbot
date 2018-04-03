cmake_minimum_required(VERSION 2.8)


add_library(basic_socket_functions STATIC sock_functions.c)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
