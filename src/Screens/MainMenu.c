void MMbg_init(GameObj* bg, SDL_Renderer* ren) {
    bg->destRect.h = WINDOW_HEIGHT;
    bg->destRect.w = WINDOW_WIDTH;
    bg->srcRect.h = WINDOW_HEIGHT;
    bg->srcRect.w = WINDOW_WIDTH;

    bg->Texture = Texture_Loader("assets/Others/Pre-Flip-Main-bg.png",ren);
    bg->ID = 1;
}

void MMtitle_init(GameObj* OB, SDL_Renderer* ren) {
    OB->destRect.h = 177;
    OB->destRect.w = 436;
    OB->destRect.y = 50;
    OB->destRect.x = WINDOW_WIDTH/2-(436/2);

    OB->srcRect.h = 177;
    OB->srcRect.w = 436;

    
    OB->Texture = Texture_Loader("assets/Others/Flipped-Legacy.png",ren);
    OB->ID = 2;
}

void MMquit_btn_effect(IntGameObj* self , SDL_Event  ByMouad, game_state* data, StaticInitFunc Statics[], IntInitFunc Inter[]){
    if(ByMouad.type==SDL_MOUSEBUTTONDOWN){
        if(ByMouad.button.x>=5 && ByMouad.button.x<=45 && ByMouad.button.y>=5 && ByMouad.button.y<=45 ){
            data->game_state = false;
        }

    }

}

void MMquit_btn_init(IntGameObj* OB, SDL_Renderer* ren){

    OB->destRect.h = 40;
    OB->destRect.w = 40;
    OB->destRect.y = 5;
    OB->destRect.x = 5;

    OB->srcRect.h = 225;
    OB->srcRect.w = 225;

    OB->Texture = Texture_Loader("assets/Others/Off-Btn.png",ren);
    OB->ID=3;

    OB->effect = MMquit_btn_effect;
    
}

void MMpressAny_init(GameObj* OB, SDL_Renderer* ren) {
    OB->destRect.h = 124;
    OB->destRect.w = 880;
    OB->destRect.y = 350;
    OB->destRect.x = WINDOW_WIDTH/2-(880/2);

    OB->srcRect.h = 124;
    OB->srcRect.w = 1280;

    
    OB->Texture = Texture_Loader("assets/Others/Press-Any.png",ren);
    OB->ID = 2;
}

void MMDot_effect(IntGameObj* self , SDL_Event e, game_state* data, StaticInitFunc Statics[], IntInitFunc Inter[]) {
    if(e.type == SDL_KEYDOWN) {
        load_LevelSelection_pg0(data->m,data->renderer,Statics,Inter);
    }
}

void MMDot_init(IntGameObj* Ob) {
    Ob->ID = 4;
    Ob->effect = MMDot_effect;
}

void load_mainMenu(manager* m ,SDL_Renderer* ren ,StaticInitFunc statics[] ,IntInitFunc inters[]) {

    GameObj* bg = m->addObject(m,ST_GENER_IMG,ren,statics);
    GameObj* title = m->addObject(m,ST_GENER_IMG,ren,statics);
    GameObj* press_any = m->addObject(m,ST_GENER_IMG,ren,statics);

    IntGameObj* quit_btn = m->addIntObject(m,INT_GENER_BTN,ren,inters);
    IntGameObj* dot = m->addIntObject(m,INT_INVIS_JOHNCENA,ren,inters);


    MMDot_init(dot);
    MMbg_init(bg,ren);
    MMtitle_init(title,ren);
    MMpressAny_init(press_any,ren);
    MMquit_btn_init(quit_btn,ren);
}


