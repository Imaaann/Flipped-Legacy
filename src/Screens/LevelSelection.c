
void LSBg_init(GameObj* Ob, SDL_Renderer* ren) {
    Ob->destRect.h = WINDOW_HEIGHT;
    Ob->destRect.w = WINDOW_WIDTH;


    Ob->srcRect.h = WINDOW_HEIGHT;
    Ob->srcRect.w = WINDOW_WIDTH;

    Ob->Texture = Texture_Loader("assets/Others/Act0-Bg.png",ren);
    Ob->ID = 1;
}

void LSBtn_effect(IntGameObj* Ob, SDL_Event e, game_state* d, StaticInitFunc Statics[], IntInitFunc Inter[]) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        if((e.button.x >= (WINDOW_WIDTH-776)/2) && (e.button.x <= ((WINDOW_WIDTH-776)/2 + 776)) && (e.button.y >= WINDOW_HEIGHT/2) && (e.button.y <= (WINDOW_HEIGHT/2 + 136))) {
            d->m->clear(d->m);            
        }
    }
}

void LSBtn_init(GameObj* Ob, SDL_Renderer* ren) {
    Ob->destRect.h = 136;
    Ob->destRect.w = 776;
    Ob->destRect.x = (WINDOW_WIDTH-776)/2;
    Ob->destRect.y = WINDOW_HEIGHT/2;



    Ob->srcRect.h = 136;
    Ob->srcRect.w = 776;

    Ob->Texture = Texture_Loader("assets/Others/Button_Long.jpeg",ren);
    Ob->ID = 2;
}

void LSTitle_init(GameObj* Ob, SDL_Renderer* ren) {
    Ob->ID = 3;

    SDL_Color col = {38,106,203};
    Ob->Texture = textLoader("Act-0: A flipped world view","assets/Others/Fonts/annyeong/AnnyeongHaseyo-GOKLO.ttf",col,48,ren);

    Ob->destRect.h = 49;
    Ob->destRect.w = 630;
    Ob->destRect.x = (WINDOW_WIDTH-628)/2;
    Ob->destRect.y = (WINDOW_HEIGHT+80)/2;

}

void LSTitleOut_init(GameObj* Ob, SDL_Renderer* ren) {
    Ob->ID = 3;

    SDL_Color col = {0,0,0};
    Ob->Texture = textLoader("Act-0: A flipped world view","assets/Others/Fonts/annyeong/AnnyeongHaseyo-GOKLO.ttf",col,50,ren);

    Ob->destRect.h = 51;
    Ob->destRect.w = 640;
    Ob->destRect.x = (WINDOW_WIDTH-638)/2;
    Ob->destRect.y = (WINDOW_HEIGHT+80)/2;

}


void load_LevelSelection_pg0(manager* m, SDL_Renderer* ren, StaticInitFunc Statics[], IntInitFunc Inter[]) {
    
    m->clear(m);

    GameObj* Bg = m->addObject(m,ST_GENER_IMG,ren,Statics);
    GameObj* Btn = m->addObject(m,ST_GENER_IMG,ren,Statics);
    GameObj* TitleOut = m->addObject(m,ST_GENER_TXT,ren,Statics);
    GameObj* Title = m->addObject(m,ST_GENER_TXT,ren,Statics);


    IntGameObj* Invis_Btn = m->addIntObject(m,INT_INVIS_JOHNCENA,ren,Inter);
    Invis_Btn->effect = LSBtn_effect;

    LSTitleOut_init(TitleOut,ren);
    LSTitle_init(Title,ren);
    LSBg_init(Bg,ren);
    LSBtn_init(Btn,ren);


}
