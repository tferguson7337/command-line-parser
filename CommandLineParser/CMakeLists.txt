cmake_minimum_required(VERSION 3.13)

# Set project name
project(CommandLineParserLib LANGUAGES CXX)


# Set root directory of CLP code
set(CLP_CODE_HDR ${CommandLineParserLib_SOURCE_DIR}/Headers)
set(CLP_CODE_SRC ${CommandLineParserLib_SOURCE_DIR}/Source)

# Location of CLP .h files
include_directories(${CLP_CODE_HDR})

# Location of CLP .cpp files
file(GLOB SOURCES "${CLP_CODE_SRC}/*.cpp")

# Location of CC .h files
include_directories(${CommandLineParserLib_SOURCE_DIR}/../CC/Headers)

# Add executable target to be built from source.
add_library(${PROJECT_NAME} ${SOURCES})

# Build using C++17, Release configuration.
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
set_target_properties(${PROJECT_NAME} PROPERTIES BUILD_TYPE Release)


if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Compile with extra flags.
    set(GCC_WARNING_FLAGS "-Wall -Wextra -Werror -pedantic -Wno-unknown-pragmas")
    message("Adding GCC flags[${GCC_WARNING_FLAGS}]")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_WARNING_FLAGS}")
endif()


# Remove any default prefix from output.
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

install(TARGETS CommandLineParserLib DESTINATION ${CommandLineParserLib_SOURCE_DIR}/build)