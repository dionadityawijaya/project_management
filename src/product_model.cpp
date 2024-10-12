#include "product_model.h"
#include <iostream>
#include <sstream>

ProductModel::ProductModel(const std::string& dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    }
}

ProductModel::~ProductModel() {
    if (db) {
        sqlite3_close(db);
    }
}

bool ProductModel::addProduct(const std::string& name, double price) {
    std::stringstream query;
    query << "INSERT INTO products (name, price) VALUES ('" << name << "', " << price << ");";
    return executeQuery(query.str());
}

bool ProductModel::updateProduct(int id, const std::string& name, double price) {
    std::stringstream query;
    query << "UPDATE products SET name = '" << name << "', price = " << price << " WHERE id = " << id << ";";
    return executeQuery(query.str());
}

bool ProductModel::deleteProduct(int id) {
    sqlite3_stmt* stmt;
    const char* query = "DELETE FROM products WHERE id = ?;";

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, id); // Bind id ke parameter query

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "SQL execution error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt); // Bebaskan statement
    return true;
}


std::vector<Product> ProductModel::getAllProducts() {
    std::vector<Product> products;
    std::string query = "SELECT id, name, price FROM products;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Product product;
            product.id = sqlite3_column_int(stmt, 0);
            product.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            product.price = sqlite3_column_double(stmt, 2);
            products.push_back(product);
        }
    } else {
        std::cerr << "Error executing SELECT statement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    return products;
}

bool ProductModel::executeQuery(const std::string& query) {
    char* errMsg = nullptr;
    int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
    
    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    
    return true;
}
