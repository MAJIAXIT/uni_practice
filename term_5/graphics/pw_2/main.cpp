#include "application.hpp"

int main() {
    Application app;

    if (!app.init()) {
        return -1;
    }

    app.run();
    app.cleanup();

    return 0;
}