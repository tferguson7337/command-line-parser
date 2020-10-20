cmake_minimum_required(VERSION 3.13)

# Set project name
project(CommandLineParser LANGUAGES CXX)

# Do the thing to grab submodule(s).
execute_process(COMMAND git submodule update --init --recursive WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(${CommandLineParser_SOURCE_DIR}/CommandLineParser)
add_subdirectory(${CommandLineParser_SOURCE_DIR}/UnitTests)