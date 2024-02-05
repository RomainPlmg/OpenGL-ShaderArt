#include "Hello_Triangle_App.h"

int main() {
    Hello_triangle_App app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        app.clearApp();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}