#include <stdbool.h>
#include <SDL2/SDL.h>

struct game_state {
    bool game_state;
    SDL_Window* window;
    SDL_Renderer* renderer;
    struct manager* m;
};


struct GameObj {

    SDL_Texture* Texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;

    int ID;
    Uint16 code;

    int x;
    int y;

    void (*render)(struct GameObj*, SDL_Renderer*);
    void (*update)(struct GameObj*);
};

typedef struct GameObj* (*StaticInitFunc)(SDL_Renderer*);
typedef struct IntGameObj* (*IntInitFunc)(SDL_Renderer*);

struct IntGameObj {
    
    SDL_Texture* Texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;

    int ID;
    Uint16 code;

    int x;
    int y;

    void (*render)(struct IntGameObj*, SDL_Renderer*);
    void (*update)(struct IntGameObj*); 
    
    // event Handling
    void (*effect)(struct IntGameObj*, SDL_Event, struct game_state*, StaticInitFunc[], IntInitFunc[]);
};


typedef struct manager {

    // Array of static objects
    Uint8 StaticCtr;
    struct GameObj* Static[MAX_MANAGER_STATIC_OBJ];

    // Array of interactive objects
    Uint8 IntCtr;
    struct IntGameObj* Inter[MAX_MANAGER_INTER_OBJ];

    //Manger methods
    struct GameObj* (*addObject)(struct manager* , Uint16 , SDL_Renderer* , StaticInitFunc[]);
    struct IntGameObj* (*addIntObject)(struct manager* , Uint16 , SDL_Renderer* , IntInitFunc[]);
    void (*removeObject)(struct manager* ,int , int);

    void (*updateAll)(struct manager*);
    void (*renderAll)(struct manager*, SDL_Renderer*);
    void (*checkAll)(struct manager*, SDL_Event, struct game_state*, StaticInitFunc[], IntInitFunc[]);
    void (*clear)(struct manager*);
    // idk add more...


} manager;

typedef struct GameObj GameObj;
typedef struct IntGameObj IntGameObj;
typedef struct game_state game_state;
