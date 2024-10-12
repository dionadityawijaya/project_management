#ifndef PRODUCT_CONTROLLER_H
#define PRODUCT_CONTROLLER_H

#include <crow.h>
#include "product_model.h"

class ProductController {
    public: 
        ProductController(ProductModel& model);

        crow::json::wvalue getAllProducts();
        crow::response addProduct(const crow::request& req);
        crow::response updateProduct(int id, const crow::request& req);
        crow::response deleteProduct(int id);

    private:
        ProductModel& model;

};

#endif