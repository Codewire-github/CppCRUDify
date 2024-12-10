#include "database.h"
#include <dotenv.h>
#include <iostream>

mysqlx::Session* session = nullptr;

void initializeDatabase() {
    //Loading .env
    dotenv::init();

    std::string host = std::getenv("DB_HOST");
    std::string user = std::getenv("DB_USER");
    std::string password = std::getenv("DB_PASSWORD");
    std::string database = std::getenv("DB_NAME");

    try {
        session = new mysqlx::Session(host, 33060, user, password);
        session->sql("USE " + database).execute();
        std::cout << "Database connection successful!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Database connection failed: " << e.what() << std::endl;
    }
}

mysqlx::Session* getSession() {
    return session;
}