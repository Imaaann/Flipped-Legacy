#include <stdbool.h>
#include <SDL2/SDL.h>

struct GameObj {

    SDL_Texture* Texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;

    int x;
    int y;


    void (*render)(struct GameObj*, SDL_Renderer*);
    void (*update)(struct GameObj*);
    void (*init)(struct GameObj*, SDL_Renderer*);
};

struct game_state {
    bool game_state;
    SDL_Window* window;
    SDL_Renderer* renderer;
};

