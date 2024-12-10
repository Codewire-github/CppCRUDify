#include "routes.h"
#include "database.h"

int main() {

    crow::SimpleApp app;

    // Initializing databse connection
    initializeDatabase();

    defineRoutes(app);

    app.port(8080).multithreaded().run();

    return 0;
}
