#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <cmath>
#include <iostream>

#define HEIGHT 700
#define WIDTH 1000

using namespace std;

class Application {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *gatesTexture;
    SDL_Texture *ballTexture;
    SDL_Texture *soccer1Texture;
    SDL_Texture *soccer2Texture;
    bool isRunning;

  public:
    Application(const char *title, int x, int y, int w, int h, Uint32 flags);
    bool running() { return isRunning; }
    void hanldeEvents();
    void render();
    SDL_Texture *getTextureFromImage(const char *path);
    ~Application();
};

SDL_Texture *Application::getTextureFromImage(const char *path) {
    static SDL_Surface *image;
    image = IMG_Load(path);
    if (image == nullptr) {
        cerr << SDL_GetError() << endl;
        isRunning = false;
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    if (texture == nullptr) {
        cerr << SDL_GetError() << endl;
        isRunning = false;
        return nullptr;
    }
    return texture;
}

Application::Application(const char *title, int x, int y, int w, int h,
                         Uint32 flags) {
    isRunning = true;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << SDL_GetError() << endl;
        isRunning = false;
        return;
    }

    if ((window = SDL_CreateWindow(title, x, y, w, h, flags)) == nullptr) {
        cerr << SDL_GetError() << endl;
        isRunning = false;
        return;
    }

    if ((renderer = SDL_CreateRenderer(window, -1, 0)) == nullptr) {
        cerr << SDL_GetError() << endl;
        isRunning = false;
        return;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        cout << SDL_GetError();
        isRunning = false;
        return;
    }

    gatesTexture = getTextureFromImage("images/gates.png");
    ballTexture = getTextureFromImage("images/ball.png");
    soccer1Texture = getTextureFromImage("images/soccer1.png");
    soccer2Texture = getTextureFromImage("images/soccer2.png");
}

void Application::hanldeEvents() {
    SDL_Event e;
    SDL_WaitEvent(&e);
    switch (e.type) {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        if (e.key.keysym.sym == SDLK_ESCAPE)
            isRunning = false;
        else if (e.key.keysym.sym == SDLK_SPACE)
            render();
        break;
    default:
        break;
    }
}

void Application::render() {
    int x, y,
        startX = WIDTH / 2 - WIDTH / 5,
        startY = HEIGHT / 2 + HEIGHT / 3.5,
        size   = WIDTH / 12;
    SDL_Rect ballRect, 
             soccerRect = {startX - 300, startY - 280, 400, 400};
    
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, gatesTexture, NULL, NULL);
    SDL_RenderCopy(renderer, soccer1Texture, NULL, &soccerRect);
    ballRect = {startX, startY, size, size};
    SDL_RenderCopy(renderer, ballTexture, NULL, &ballRect);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);

    for (x = startX, y = startY; x < 650; x += 5, y -= 5) {
        if (x % 10 == 0)
            size -= 1;
        SDL_RenderCopy(renderer, gatesTexture, NULL, NULL);
        SDL_RenderCopy(renderer, soccer2Texture, NULL, &soccerRect);
        ballRect = {x, y, size, size};
        SDL_RenderCopy(renderer, ballTexture, NULL, &ballRect);
        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }
}

Application::~Application() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    IMG_Quit();
}