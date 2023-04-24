cmake_minimum_required(VERSION 3.24)
project(PasswordSaver)

set(CMAKE_CXX_STANDARD 17)

add_executable(PasswordSaver main.cpp sqlite/sqlite3.c)
