#include "product_controller.h"
#include "product_model.h"

int main(int argc, char const *argv[])
{
    crow::SimpleApp app;

    ProductModel model("data/products.db");
    ProductController controller(model);

    // Route untuk GET semua produk
    CROW_ROUTE(app, "/products")
    .methods(crow::HTTPMethod::GET)
    ([&controller]() {
        return controller.getAllProducts();
    });

    // Route untuk menambahkan produk baru (POST)
    CROW_ROUTE(app, "/product")
    .methods(crow::HTTPMethod::POST)
    ([&controller](const crow::request& req) {
        return controller.addProduct(req); // Parameter request harus diteruskan ke fungsi
    });

    // Route untuk memperbarui produk (POST dengan id)
    CROW_ROUTE(app, "/product/<int>")
    .methods(crow::HTTPMethod::POST)
    ([&controller](int id, const crow::request& req) {
        return controller.updateProduct(id, req); // id dan request harus diteruskan
    });

    // Route untuk menghapus produk (DELETE dengan id)
    CROW_ROUTE(app, "/product/<int>")
    .methods(crow::HTTPMethod::DELETE)
    ([&controller](int id) {
        return controller.deleteProduct(id);
    });


    app.port(3000).multithreaded().run();
}
