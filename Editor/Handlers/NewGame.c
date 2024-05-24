#include <ncurses/ncurses.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>

//#include "EditorTypes.h" // Remember to remove this

void createGameDirectories(const char *gameName) {
    char path[256];

    // Base directory path
    snprintf(path, sizeof(path), "Games\\%s", gameName);
    if (_mkdir(path) == -1) {
        return;
    }

    // Subdirectories
    const char *subDirs[] = {
        "Characters",
        "Bestiary",
        "Levels",
        "Assets",
        "Assets\\Bg",
        "Assets\\Models",
        "Assets\\Icons",
        "Assets\\Card_bg",
        "Assets\\Ult_bg"
    };

    // Create each subdirectory
    for (int i = 0; i < sizeof(subDirs) / sizeof(subDirs[0]); ++i) {
        snprintf(path, sizeof(path), "Games\\%s\\%s", gameName, subDirs[i]);
        if (_mkdir(path) == -1) {
            return;
        }
    }
}

void createInputWindow(WINDOW* w) {
    wclear(w);
    box(w,0,0);
    mvwprintw(w,1,1,"HP:");
    mvwprintw(w,1,40,"| HP/Lvl:");
    mvwprintw(w,2,1,"ATK:");
    mvwprintw(w,2,40,"| ATK/Lvl:");
    mvwprintw(w,3,1,"DEF:");
    mvwprintw(w,3,40,"| DEF/Lvl:");
    mvwprintw(w,4,1,"RES:");
    mvwprintw(w,4,40,"| RES/Lvl:");
}

void readInputWindow(WINDOW* w, FL_Character* c) {
    mvwscanw(w,1,4,"%d",&c->HP.MAX_HP);
    mvwscanw(w,1,49,"%d",&c->Hp_g);
    mvwscanw(w,2,5,"%d",&c->ATK);
    mvwscanw(w,2,50,"%d",&c->Atk_g);
    mvwscanw(w,3,5,"%d",&c->DEF);
    mvwscanw(w,3,50,"%d",&c->Def_g);
    mvwscanw(w,4,5,"%d",&c->RES);
    mvwscanw(w,4,50,"%d",&c->Res_g);
}

void NewGame() {
    FL_GAME_DATA Game;


    int maxX,maxY;
    getmaxyx(stdscr,maxY,maxX);
    WINDOW* inputwin = newwin(5,96,12,(maxX-96)/2);
    box(inputwin,0,0);
    wrefresh(inputwin);

    mvwprintw(inputwin,1,1,"Name: ");
    mvwprintw(inputwin,2,1,"Char Num: ");
    mvwprintw(inputwin,3,1,"Enem Num: ");
    wrefresh(inputwin);

    char buff[512];
    int Cnum = 0;
    int Enum = 0;
    wrefresh(inputwin);

    mvwscanw(inputwin,1,7,"%[^\n]s",buff);
    mvwscanw(inputwin,2,11,"%d",&Cnum);
    mvwscanw(inputwin,3,11,"%d",&Enum);

    strncpy(Game.Name,buff,256);
    wclear(inputwin);


    //Game Directories
    createGameDirectories(Game.Name);

    //Character creation
    FL_Character character;

    inputwin = newwin(7,96,12,(maxX-96)/2);
    box(inputwin,0,0);
    for (int i=0; i<Cnum; i++) {
        createInputWindow(inputwin);
        readInputWindow(inputwin,&character);
    }



    



}

