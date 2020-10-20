cmake_minimum_required(VERSION 3.13)

# Set project name
project(CLPUnitTests LANGUAGES CXX)


# Set root directory of CLP unit test code
set(CLP_TEST_CODE_ROOT ${CLPUnitTests_SOURCE_DIR})

# Location of CLP unit test .h files
include_directories(${CLP_TEST_CODE_ROOT}/Headers)


# Location of CLP .cpp files
file(GLOB SOURCES "${CLP_TEST_CODE_ROOT}/Source/*.cpp")


# Add executable target to be built from source.
add_executable(${PROJECT_NAME} ${SOURCES})


# Build using C++17, Release configuration.
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
set_target_properties(${PROJECT_NAME} PROPERTIES BUILD_TYPE Release)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Compile with extra flags.
    set(GCC_WARNING_FLAGS "-Wall -Wextra -Werror -pedantic -Wno-unknown-pragmas -pthread")
    message("Adding GCC warning flags[${GCC_WARNING_FLAGS}]")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_WARNING_FLAGS}")
endif()


# Set root directory of CLP project and code.
set(CLP_CODE_ROOT ${CLP_TEST_CODE_ROOT}/../CommandLineParser)

# Location of CLP .h files
include_directories(${CLP_CODE_ROOT}/Headers)

# Location of CC .h files
include_directories(${CLP_TEST_CODE_ROOT}/../CC/Headers)

# Link in CommandLineParserLib
target_link_libraries(${PROJECT_NAME} CommandLineParserLib)


# Set root directory of SUTL project and code
set(SUTL_PROJ_ROOT ${CLP_TEST_CODE_ROOT}/SUTL)
set(SUTL_CODE_ROOT ${SUTL_PROJ_ROOT}/SimpleUnitTestLibrary)

# Location of SUTL .h files
include_directories(${SUTL_CODE_ROOT}/Headers)

# Add submodule root as a subdirectory, which should cause it to be built automagically.
add_subdirectory(${SUTL_PROJ_ROOT})

# Link in SUTL
target_link_libraries(${PROJECT_NAME} SUTL)


# Remove any default prefix from output.
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

install(TARGETS CLPUnitTests DESTINATION ${CLPUnitTests_SOURCE_DIR}/build)