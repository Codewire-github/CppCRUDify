#include <iostream>
#include <dotenv.h>
#include <crow.h>

int main() {

    dotenv::init();

    const char* db_host = std::getenv("DB_HOST");
    const char* db_user = std::getenv("DB_USER");
    const char* db_password = std::getenv("DB_PASSWORD");
    const char* db_name = std::getenv("DB_NAME");

    if (db_host == nullptr || db_user == nullptr || db_password == nullptr || db_name == nullptr) {
        std::cerr << "Failed to load environment variables" << std::endl;
        return 1;
    }

    std::cout << "DB_HOST: " << db_host << std::endl;
    std::cout << "DB_USER: " << db_user << std::endl;
    std::cout << "DB_PASSWORD: " << db_password << std::endl;
    std::cout << "DB_NAME: " << db_name << std::endl;

    crow::SimpleApp app;

    app.route_dynamic("/")([]() {
        return "Hello, Crow!";
    });

    app.port(8080).multithreaded().run();

    return 0;
}
