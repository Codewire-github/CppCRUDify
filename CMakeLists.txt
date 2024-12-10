cmake_minimum_required(VERSION 3.11)

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

# Set the include directory for MySQL Connector X DevAPI
set(MYSQL_CONNECTOR_INCLUDE_DIR /opt/homebrew/Cellar/mysql-connector-c++/9.1.0/include/mysqlx)
set(MYSQL_CONNECTOR_LIBRARY /opt/homebrew/Cellar/mysql-connector-c++/9.1.0/lib/libmysqlcppconnx.dylib)

# Verify MySQL Connector installation
if(NOT EXISTS ${MYSQL_CONNECTOR_INCLUDE_DIR}/xdevapi.h)
    message(FATAL_ERROR "MySQL Connector C++ X DevAPI headers not found in ${MYSQL_CONNECTOR_INCLUDE_DIR}")
endif()

if(NOT EXISTS ${MYSQL_CONNECTOR_LIBRARY})
    message(FATAL_ERROR "MySQL Connector C++ library not found at ${MYSQL_CONNECTOR_LIBRARY}")
endif()

message(STATUS "Found MySQL Connector C++ include directory: ${MYSQL_CONNECTOR_INCLUDE_DIR}")
message(STATUS "Found MySQL Connector C++ library: ${MYSQL_CONNECTOR_LIBRARY}")

# Add the executable for your project
add_executable(CppCRUDify src/main.cpp src/database.cpp src/routes.cpp)

# Include directories for ASIO and dotenv-cpp
target_include_directories(CppCRUDify PRIVATE ${ASIO_INCLUDE_DIR} ${MYSQL_CONNECTOR_INCLUDE_DIR} ${dotenv-cpp_SOURCE_DIR}/include/laserpants/dotenv)

target_link_libraries(CppCRUDify PRIVATE Crow  ${MYSQL_CONNECTOR_LIBRARY})


message(STATUS "Crow and dotenv-cpp, and MySQL Connector C++ successfully configured!")
