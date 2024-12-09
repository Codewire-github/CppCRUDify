cmake_minimum_required(VERSION 3.10)

# Project name
project(CppCRUDify)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

# Fetching Crow library
FetchContent_Declare(
    crow
    GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
    GIT_TAG master
)
FetchContent_MakeAvailable(crow)

# Fetching dotenv-cpp library
FetchContent_Declare(
    dotenv-cpp
    GIT_REPOSITORY https://github.com/laserpants/dotenv-cpp.git
    GIT_TAG master
)
FetchContent_MakeAvailable(dotenv-cpp)

# Finding and linking ASIO (installed via Homebrew)
find_path(ASIO_INCLUDE_DIR asio.hpp)
if(NOT ASIO_INCLUDE_DIR)
    message(FATAL_ERROR "asio not found!")
endif()

message(STATUS "Found ASIO at: ${ASIO_INCLUDE_DIR}")

# Add the executable for your project
add_executable(CppCRUDify src/main.cpp)

# Include directories for ASIO and dotenv-cpp
target_include_directories(CppCRUDify PRIVATE ${ASIO_INCLUDE_DIR} ${dotenv-cpp_SOURCE_DIR}/include/laserpants/dotenv)

target_link_libraries(CppCRUDify PRIVATE Crow)


message(STATUS "Crow and dotenv-cpp successfully configured!")
