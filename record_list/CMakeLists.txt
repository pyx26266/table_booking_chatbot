cmake_minimum_required(VERSION 2.8)


add_library(record_list STATIC record_linked_list.c)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
