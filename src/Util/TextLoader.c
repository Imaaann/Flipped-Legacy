#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


SDL_Texture* textLoader(const char* text, const char* font_path, SDL_Color color, int size, SDL_Renderer* ren) {
    TTF_Font* Font = TTF_OpenFont(font_path,size);
    
    SDL_Surface* tmpSurface = TTF_RenderText_Blended(Font,text,color);
    printf("Text Surface: %d,%d\n",tmpSurface->h,tmpSurface->w);

    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(ren,tmpSurface);

    SDL_FreeSurface(tmpSurface);
    return text_texture;
} 