#include "routes.h"
#include "database.h"

void defineRoutes(crow::SimpleApp& app) {
    // Create
    CROW_ROUTE(app, "/create").methods("POST"_method)([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(400, "Invalid JSON");
        }

        try {
            auto session = getSession();
            std::string name = body["name"].s();
            int value = body["value"].i();
            session->sql("INSERT INTO items (name, value) VALUES (?, ?)").bind(name, value).execute();
            return crow::response(201, "Item created");

        }
        catch (const std::exception& e) {
            return crow::response(500, e.what());
        }
        });

    // Read
    CROW_ROUTE(app, "/read/<int>").methods("GET"_method)([](int id) {
        try {
            auto session = getSession();
            auto result = session->sql("SELECT * FROM items WHERE id = ?").bind(id).execute();
            auto row = result.fetchOne();

            if (!row) {
                return crow::response(404, "Item not found");
            }
            crow::json::wvalue response;
            response["id"] = row[0].get<int>();
            response["name"] = row[1].get<std::string>();
            response["value"] = row[2].get<int>();
            return crow::response(response);
        }
        catch (const std::exception& e) {
            return crow::response(500, e.what());
        }
        });

    // Update
    CROW_ROUTE(app, "/update/<int>").methods("PUT"_method)([](const crow::request& req, int id) {
        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(400, "Invalid JSON");
        }

        try {
            auto session = getSession();
            std::string name = body["name"].s();
            int value = body["value"].i();
            session->sql("UPDATE items SET name = ?, value = ? WHERE id = ?").bind(name, value, id).execute();
            return crow::response(200, "Item updated");
        }
        catch (const std::exception& e) {
            return crow::response(500, e.what());
        } 
        });

    // Delete
    CROW_ROUTE(app, "/delete/<int>").methods("DELETE"_method)([](int id) {
        try {
            auto session = getSession();
            session->sql("DELETE FROM items WHERE id = ?").bind(id).execute();
            return crow::response(200, "Item deleted");
        }
        catch (const std::exception& e) {
            return crow::response(500, e.what());
        }
        });
}