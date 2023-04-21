cmake_minimum_required(VERSION 3.10)

project(hello)

aux_source_directory(../ DIR_SRCS)

include_directories(include)

add_executable(hello ${DIR_SRCS})