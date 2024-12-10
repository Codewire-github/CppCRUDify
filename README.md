# CppCRUDify
A lightweight and efficient CRUD backend server built with C++, Crow framework, and MySQL integration. It features seamless environment variable support using .env files and a modular architecture for managing routes and database operations.

## Features

- **Create**: Add a new item to the database.
- **Read**: Retrieve an item by ID from the database.
- **Update**: Modify an existing item in the database.
- **Delete**: Remove an item from the database.

## Requirements

- **C++ Compiler** (C++17 or later) - [GCC](https://gcc.gnu.org/) or [Clang](https://clang.llvm.org/)
- **CMake** (for building the project) - [CMake Installation Guide](https://cmake.org/install/)
- **Asio** - [Asio Download](https://think-async.com/Asio/)
- **Crow** (C++ web framework) - [Crow GitHub Repository](https://github.com/CrowCpp/Crow)
- **dotenvcpp** (.env file reading library) - [dotenv-cpp Repository](https://github.com/laserpants/dotenv-cpp)
- **MySQL** (Relational Database) - [MySQL Download](https://dev.mysql.com/downloads/)
- **MySQL-Connector-cpp** (library to connect MySQL Database to C++) [MySQL Connector/C++ Download](https://dev.mysql.com/downloads/connector/cpp/)

## Installation

### 1. Clone the repository
```bash
git clone https://github.com/Codewire-github/CppCRUDify.git
cd CppCRUDify
```
### 2. Install dependencies
#### On macOS (Homebrew)
```bash
brew install crow mysql asio mysql-connector-c++
```
#### On Ubuntu
```bash
sudo apt-get install libmysqlcppconn-dev libasio-dev
```
### 3. Install MySQL
Follow the [MySQL installation guide](https://dev.mysql.com/downloads/installer/) to install MySQL on your system. You will also need to set up a MySQL database for the application.

### 4. Update the CMake file for MySQL-connector PATH
You need to update the path for MySQL-connector-C++ library in `CMakeLists.txt`, following is the path for macOS:
```cmake
# Set the include directory for MySQL Connector X DevAPI
set(MYSQL_CONNECTOR_INCLUDE_DIR /opt/homebrew/Cellar/mysql-connector-c++/9.1.0/include/mysqlx)
set(MYSQL_CONNECTOR_LIBRARY /opt/homebrew/Cellar/mysql-connector-c++/9.1.0/lib/libmysqlcppconnx.dylib)

```

### 5. Build the project using CMake
```bash
mkdir build
cd build
```
Put your .env file inside the `/build` folder. Example of `.env` file:
```env
DB_HOST=localhost
DB_USER=root
DB_PASSWORD=yourpassword
DB_NAME=yourdatabaseName
```
Then build the cmake project:
```bash
cmake ..
make
```
### 6. Run the application
```bash
./CppCRUDify
```
The application will start a web server and listen for requests on `http:://localhost:8080`

## API Endpoints

### 1. Create Item
- **URL**: `/create`
- **Method**: `POST`
- **Request Body** (JSON):
    ```json
    {
        "name": "Item Name",
        "value": 100
    }
    ```
- **Response**:
    - `201 Created`: Item created
    - `400 Bad Request`: Invalid JSON
    - `500 Internal Server Error`: Database error

### 2. Read Item by ID
- **URL**: `/read/<int:id>`
- **Method**: `GET`
- **Request Body** (JSON):
    ```json
    {
        "id": 1,
        "name": "Item Name",
        "value": 100
    }
    ```
- **Response**:
    - `404 Not Found`: Item not found
    - `500 Internal Server Error`: Database error

### 3. Update Item
- **URL**: `/update/<int:id>`
- **Method**: `PUT`
- **Request Body** (JSON):
    ```json
    {
        "name": "Updated Item Name",
        "value": 200
    }
    ```
- **Response**:
    - `200 OK`: Item updated successfully
    - `400 Bad Request`: Invalid JSON
    - `500 Internal Server Error`: Database error

### 4. Delete Item
- **URL**: `/delete/<int:id>`
- **Method**: `DELETE`
- **Response**:
    - `200 OK`: Item deleted successfully
    - `500 Internal Server Error`: Database error


## Example CURL Commands
To test the API, you can use the following curl commands:

### 1. Create Item
```bash
curl -X POST http://localhost:8080/create -H "Content-Type: application/json" -d '{"name": "New Item", "value": 150}'
```
### 2. Read Item by ID
```bash
curl http://localhost:8080/read/1
```
### 3. Update Item
```bash
curl -X PUT http://localhost:8080/update/1 -H "Content-Type: application/json" -d '{"name": "Updated Item", "value": 200}'
```
### 4. Delete Item
```bash
curl -X DELETE http://localhost:8080/delete/1
```

## Project Structure
```makefile
CppCRUDify/
├── CMakeLists.txt         # CMake configuration file
├── README.md              # This file
├── src/
│   ├── main.cpp           # Main entry point for the application
│   ├── database.cpp       # Database connection and queries using MySQL
│   └── routes.cpp         # API route definitions
│   ├── database.h         # Header for database functions
│   └── routes.h           # Header for route definitions
└── build/                 # Build directory (created during build)
│   └── .env               # Database configuration file

```

