#ifndef PRODUCT_MODEL_H
#define PRODUCT_MODEL_H

#include <sqlite3.h>
#include <string>
#include <vector>

struct Product {
    int id;
    std::string name;
    double price;
};

class ProductModel {
    public:
        ProductModel(const std::string& dbpath);
        ~ProductModel();

        bool addProduct(const std::string& name, double price);
        bool updateProduct(int id, const std::string& name, double price);
        bool deleteProduct(int id);
        std::vector<Product> getAllProducts();

    private:
        sqlite3* db;
        bool executeQuery(const std::string& query);
};

#endif