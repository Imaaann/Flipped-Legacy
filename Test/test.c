#include <stdio.h>
#include "../src/constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

SDL_Texture* BG_Text;
SDL_Rect srcRect,destRect;

int is_game_running = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int last_frame_time = 0;

int init_window(void);
void process_input();
void destroy_window();
void update();
void render();
void setup();

int main(int argc, char* argv[]) {
    is_game_running = init_window();

    Uint32 frameStart;
    int frameTime;

    setup();

    while (is_game_running) {

        frameStart = SDL_GetTicks();

        process_input();
        update();
        render();

        frameTime = SDL_GetTicks() - frameStart;

        printf("Frame Time: %d\n",frameTime);
        if (FRAME_TARGET_TIME > frameTime) {
            SDL_Delay(FRAME_TARGET_TIME - frameTime);
        }
    }

    destroy_window();

    return 0;
}

int init_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error intitializing SDL.\n");
        return false;
    }

    window = SDL_CreateWindow(
        "Test",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
    );

    if (!window) {
        fprintf(stderr,"Error creating SDL window.\n");
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr,"Error creating SDL renderer.\n");
        return false;
    }

    SDL_Surface* tmpSurface = IMG_Load("Test/Test.png");
    BG_Text = SDL_CreateTextureFromSurface(renderer,tmpSurface);
    SDL_FreeSurface(tmpSurface);

    return true;
}

void destroy_window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {

        case SDL_QUIT:
            is_game_running = false;
            break;

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                is_game_running = false;
            }
            break;

    }

}

void update() {
    destRect.x += 10;
}

void render() {
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, BG_Text, NULL, &destRect);

    SDL_RenderPresent(renderer);
}

void setup() {
    destRect.h = 256;
    destRect.w = 256;
    destRect.x = 0;
    destRect.y = 0;
}