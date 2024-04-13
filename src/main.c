#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "constants.h"
#include "texture_loader.c"

#include "GameObjs/Main_Background.c"

// Global Game state variable + Initilization
struct game_state game = {
    .game_state = false,
    .window = NULL,
    .renderer = NULL,
};

struct GameObj Background;



void setup(void);
void Process_Input(void);
void Update(void);
void Render(void);

int Init_Window(void);
void Destroy_Window(void);

int main(int argc, char* argv[]) {

    game.game_state = Init_Window();

    /*
    * For frame Capping
    * Not really needed tbh but yeah
    */
    Uint32 frameStart;
    int frameTime;

    setup();

    while(game.game_state) {
        frameStart = SDL_GetTicks();

        Process_Input();
        Update();
        Render();

        frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_TARGET_TIME > frameTime) {
            SDL_Delay(FRAME_TARGET_TIME - frameTime);
        }

    }

    Destroy_Window();

    return 0;
}

void Render(void) {
    SDL_RenderClear(game.renderer);

    (*Background.render)(&Background,game.renderer);

    SDL_RenderPresent(game.renderer);

}

void setup(void) {
    Background_init(&Background,game.renderer);
}

void Update(void) {
    (*Background.update)(&Background);
}

void Process_Input(void) {
    SDL_Event event;

    SDL_PollEvent(&event);

    switch (event.type) {

        case SDL_QUIT:
            game.game_state = false;
        break;

        case SDL_KEYDOWN:

            switch (event.key.keysym.sym) {

                case SDLK_ESCAPE:
                    game.game_state = false;
                break;

            }

        break;

    }

}

void Destroy_Window(void) {
    SDL_DestroyRenderer(game.renderer);
    SDL_DestroyWindow(game.window);
    SDL_Quit();
}

int Init_Window(void) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        perror("Error initializing SDL!\n");
        return false;
    }

    // Initialize SDL window
    game.window = SDL_CreateWindow(
        "Flipped-Legacy",
        SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,WINDOW_HEIGHT,
        0
    );

    if (!game.window) {
        perror("Error initializing SDL window!\n");
        return false;
    }

    // Initialize SDL renderer
    game.renderer = SDL_CreateRenderer(game.window,-1,0);
    if (!game.renderer) {
        perror("Error initializing SDL renderer!\n");
        return false;
    }

    return true;
}