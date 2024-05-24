#include <ncurses/ncurses.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>

//#include "EditorTypes.h" // Remember to remove this
#include "../Cards/NewCard.c"

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
    mvwprintw(w,1,1,"Name:");
    mvwprintw(w,1,40,"| Image Path:");
    mvwprintw(w,2,1,"HP:");
    mvwprintw(w,2,40,"| HP/Lvl:");
    mvwprintw(w,3,1,"ATK:");
    mvwprintw(w,3,40,"| ATK/Lvl:");
    mvwprintw(w,4,1,"DEF:");
    mvwprintw(w,4,40,"| DEF/Lvl:");
    mvwprintw(w,5,1,"RES:");
    mvwprintw(w,5,40,"| RES/Lvl:");
    mvwprintw(w,6,1,"SPD:");
    mvwprintw(w,6,40,"| Cost (1-5):");
    mvwprintw(w,7,1,"SP Regen Methods: ");
}

void readInputWindow(WINDOW* w, FL_Character* c) {
    int tmp;
    mvwscanw(w,1,6,"%[^\n]s",c->Name);
    mvwscanw(w,1,53,"%[^\n]s",c->Card_Bg);
    mvwscanw(w,2,4,"%d",&c->HP.MAX_HP);
    mvwscanw(w,2,49,"%d",&c->Hp_g);
    mvwscanw(w,3,5,"%d",&c->ATK);
    mvwscanw(w,3,50,"%d",&c->Atk_g);
    mvwscanw(w,4,5,"%d",&c->DEF);
    mvwscanw(w,4,50,"%d",&c->Def_g);
    mvwscanw(w,5,5,"%d",&c->RES);
    mvwscanw(w,5,50,"%d",&c->Res_g);
    mvwscanw(w,6,5,"%d",&c->SPD);
    mvwscanw(w,6,53,"%d",&tmp);
    tmp = (tmp - 1) % 5;
    c->cost = tmp;

    keypad(w,true);
    init_pair(2,COLOR_GREEN,COLOR_BLACK);
    init_pair(3,COLOR_RED,COLOR_BLACK);
    init_pair(4,COLOR_YELLOW,COLOR_BLACK);
    const char* choices[] = {"AUTOMATIC","OFFENSIVE","DEFENSIVE"};
    int choice = -1;
    int h=0;
    do {

        wattron(w,COLOR_PAIR(h+2));
        mvwprintw(w,7,19,"%s",choices[h]);
        wattroff(w,COLOR_PAIR(h+2));
        choice = wgetch(w);

        switch (choice) {
        case KEY_UP:
            h = (h-1) % 3;
            if (h<0) h = 2;
            break;

        case KEY_DOWN:
            h = (h+1) % 3;
            break;
        
        default:
            break;
        }

        
    } while (choice != 10);

    c->regen = h;



    

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

    inputwin = newwin(9,96,12,(maxX-96)/2);
    box(inputwin,0,0);
    int ID = 0;
    for (int i=0; i<Cnum; i++) {
        createInputWindow(inputwin);
        readInputWindow(inputwin,&character);

        character.ID = ++ID;
        character.isUnlocked = false;
        character.Unlocked_Deck = 2;

        character.Normal_Attack = NewCard(inputwin,NORMAL);
        for (int j=0; j<(2+character.cost); j++) {
            character.Deck[i] = NewCard(inputwin,INCANTATION); 
        }
        character.Ult = NewCard(inputwin,ULTIMATE);




    }



    



}

