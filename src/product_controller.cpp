#include "product_controller.h"
#include <json/json.h>

ProductController::ProductController(ProductModel& model) : model(model) {}

crow::json::wvalue ProductController::getAllProducts() {
    auto products = model.getAllProducts();
    crow::json::wvalue x;
    for (const auto& product : products) {
        x[std::to_string(product.id)] = crow::json::wvalue{
            {"name", product.name},
            {"price", product.price}
        };
    }
    return x;
}
crow::response ProductController::addProduct(const crow::request& req) {
    auto body = crow::json::load(req.body);
    if (!body) return crow::response(400);

    std::string name = body["name"].s();
    double price = body["price"].d();

    model.addProduct(name, price);
    return crow::response(201);
}

crow::response ProductController::updateProduct(int id, const crow::request& req) {
    auto body = crow::json::load(req.body);
    if (!body) return crow::response(400);

    std::string name = body["name"].s();
    double price = body["price"].d();

    model.updateProduct(id, name, price);
    return crow::response(201);
}

crow::response ProductController::deleteProduct(int id) {
    try {
        if (model.deleteProduct(id)) {
            return crow::response(crow::status::NO_CONTENT); // 204 No Content
        } else {
            return crow::response(crow::status::NOT_FOUND); // 404 Not Found
        }
    } catch (const std::exception& e) {
        // Log exception if necessary
        return crow::response(crow::status::INTERNAL_SERVER_ERROR); // 500 Internal Server Error
    }
}



