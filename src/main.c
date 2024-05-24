#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "FL_Include.c"


// Global Game state variable + Initilization
game_state game = {
    .game_state = false,
    .window = NULL,
    .renderer = NULL,
};

StaticInitFunc Static_objs[MAX_GLOBAL_OBJS];
IntInitFunc Inter_objs[MAX_GLOBAL_OBJS];

manager humble;



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

    humble.clear(&humble);
    Destroy_Window();

    return 0;
}

void setup(void) {

    init_InterDictionary(Inter_objs,MAX_GLOBAL_OBJS);
    init_StaticDictionary(Static_objs,MAX_GLOBAL_OBJS);
    manager_init(&humble);
    game.m = &humble;
    load_mainMenu(&humble,game.renderer,Static_objs,Inter_objs);

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

    humble.checkAll(&humble,event,&game,Static_objs,Inter_objs);

}

void Update(void) {
    humble.updateAll(&humble);
}

void Render(void) {

    SDL_RenderClear(game.renderer);

    humble.renderAll(&humble,game.renderer);

    SDL_RenderPresent(game.renderer);

}






void Destroy_Window(void) {
    IMG_Quit();
    TTF_Quit();
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
        SDL_WINDOW_ALLOW_HIGHDPI
    );

    if (!game.window) {
        perror("Error initializing SDL window!\n");
        return false;
    }

    // Initialize SDL renderer
    game.renderer = SDL_CreateRenderer(game.window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!game.renderer) {
        perror("Error initializing SDL renderer!\n");
        return false;
    }

    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int img_init_status = IMG_Init(flags);
    if (img_init_status != flags) {
        perror("Error initializing SDL Image");
        return false;
    }

    if (TTF_Init() < 0) {
        perror("Error initializing SDL TTF");
        return false;
    }


    return true;
}
