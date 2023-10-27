#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>
#include <iostream>

#define HEIGHT 700
#define WIDTH 700

using namespace std;

class Application {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    bool isRunning;

  public:
    Application(const char *title, int x, int y, int w, int h, Uint32 flags);
    bool running() { return isRunning; }
    void hanldeEvents();
    void drawFunc(double (*func)(double x), double lint, double rint);
    void makeAxis();
    void writeText(SDL_Rect *rect, const char *msg);
    ~Application();
};

Application::Application(const char *title, int x, int y, int w, int h,
                         Uint32 flags) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << SDL_GetError() << endl;
        isRunning = false;
        return;
    }
    // Initialize font
    if (TTF_Init() != 0) {
        cerr << SDL_GetError() << endl;
        isRunning = false;
        return;
    }
    // Open font
    if ((font = TTF_OpenFont("/FiraCode-Retina.ttf", 14)) == NULL) {
        cerr << SDL_GetError() << endl;
        isRunning = false;
        return;
    }

    // Create window
    if ((window = SDL_CreateWindow(title, x, y, w, h, flags)) == nullptr) {
        cerr << SDL_GetError() << endl;
        isRunning = false;
        return;
    }
    // Create Renderer
    if ((renderer = SDL_CreateRenderer(window, -1, 0)) == nullptr) {
        cerr << SDL_GetError() << endl;
        isRunning = false;
        return;
    }
    isRunning = true;
}

void Application::hanldeEvents() {
    SDL_Event e;
    SDL_WaitEvent(&e);
    switch (e.type) {
    // X button pressed or ⌘ + q
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        if (e.key.keysym.sym == SDLK_ESCAPE)
            isRunning = false;
        break;
    default:
        break;
    }
}

void Application::writeText(SDL_Rect *rect, const char *msg) {
    SDL_Color color = {0, 0, 0, 0};

    SDL_Surface *fontSurface;
    fontSurface = TTF_RenderText_Solid(font, msg, color);
    if (fontSurface == nullptr) {
        cout << SDL_GetError();
        return;
    }
    SDL_Texture *fontTexture = SDL_CreateTextureFromSurface(renderer, fontSurface);
    if (fontTexture == nullptr) {
        cout << SDL_GetError();
        return;
    };

    SDL_RenderCopy(renderer, fontTexture, NULL, rect);
}

#define SCALE 45

SDL_FPoint mathToScreen(double mx, double my) {
    int x = WIDTH / 2, y = HEIGHT / 2;
    SDL_FPoint p = {static_cast<float>((x + mx * SCALE)),
                    static_cast<float>((y - my * SCALE))};
    return p;
}

void Application::makeAxis() {
    SDL_Surface *image = SDL_LoadBMP("oxy.bmp");
    if (image == nullptr) {
        cout << SDL_GetError();
        return;
    }
    SDL_Texture *imageTexture = SDL_CreateTextureFromSurface(renderer, image);
    if (imageTexture == nullptr) {
        cout << SDL_GetError();
        return;
    }
    SDL_RenderCopy(renderer, imageTexture, NULL, NULL);

    SDL_Rect dst = {static_cast<int>(mathToScreen(M_PI / 2, -0.2).x - 10),
                    static_cast<int>(mathToScreen(M_PI / 2, -0.2).y),
                    30, 20};
    writeText(&dst, "pi/2");

    dst = {static_cast<int>(mathToScreen(M_PI * 2, 0.7).x - 10),
           static_cast<int>(mathToScreen(M_PI * 2, 0.7).y),
           30, 20};
    writeText(&dst, "2pi");
}

void Application::drawFunc(double (*func)(double x), double lint, double rint) {
    SDL_RenderClear(renderer);
    makeAxis();

    // Drawing starts here
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    SDL_FPoint points[/*Count of points in interval*/
                      static_cast<int>((rint - lint) * 10 + 1)];
    int idx = 0;
    for (double x = lint; x < rint; x += 0.1) {
        points[idx++] = mathToScreen(x, func(x));
    }
    // Link points to one line
    SDL_RenderDrawLinesF(renderer, points, idx - 1);

    // Write the function
    SDL_Rect dst = {static_cast<int>(mathToScreen(4*M_PI/3, 2).x - 50),
                    static_cast<int>(mathToScreen(4*M_PI/3, 2).y),
                    150, 20};
    writeText(&dst, "y=(1/x)+2sin(x)");
    SDL_RenderPresent(renderer);
}

Application::~Application() {
    TTF_CloseFont(font);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    TTF_Quit();
}
