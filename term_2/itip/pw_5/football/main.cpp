#include "Application.hpp"

int main() {
    Application *app;
    try {
        app = new Application("Main", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,
                              SDL_WINDOW_OPENGL);
    } catch (bad_alloc &e) {
        cerr << "Error while allocating memory. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    while (app->running()) {
        app->hanldeEvents();
    }

    delete app;
    exit(EXIT_SUCCESS);
}