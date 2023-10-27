#include "Application.hpp"

double func(double x) { return (1 / x) + 2 * sin(x); }

int main() {
    Application *app;
    try {
        app = new Application("Main", 
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WIDTH, HEIGHT,
                              SDL_WINDOW_OPENGL);
    } catch (bad_alloc &e) {
        cerr << "Error while allocating memory. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    app->drawFunc(func, M_PI / 2, M_PI * 2);

    while (app->running()) {
        app->hanldeEvents();
    }

    delete app;
    exit(EXIT_SUCCESS);
}