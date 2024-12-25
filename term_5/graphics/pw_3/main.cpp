#include "application.hpp"

int main() {
    Application app;

    if (!app.init()) {
        exit(-1);
    }
    app.run();

    return 0;
}