#include <ncurses/ncurses.h>
//#include "../EditorTypes.h"


void CreateInputWindow(WINDOW* w, FL_CARD_TYPE t, int n) {
    const char* types[] = {"Normal","Incantation","Ultimate"};

    wclear(w);
    box(w,0,0);
    mvwprintw(w,0,1,"Card Editor (%s/%d) ",types[t],n);
    mvwprintw(w,1,1,"Name:");
    mvwprintw(w,1,40,"| Image Path:");
    mvwprintw(w,2,1,"Lore:");
    if (t != ULTIMATE) mvwprintw(w,2,40,"| Type:");
}

void ReadInputWindow(WINDOW* w,FL_CARD_TIER* card,FL_CARD_TYPE t) {
    mvwscanw(w,1,6,"%[^\n]s",card->Name);
    mvwscanw(w,1,53,"%[^\n]s",card->Bg_path);
    mvwscanw(w,2,6,"%[^\n]s",card->Lore);

    init_pair(5,COLOR_CYAN,COLOR_BLACK);
    init_pair(6,COLOR_MAGENTA,COLOR_BLACK);
    if (t != ULTIMATE) {   
        
        keypad(w,true);
        const char* choices[] = {"HEAL","ATTACK","COUNTER","BUFF","DEBUFF"};
        int choice = -1;
        int h=0;
        do {

            wattron(w,COLOR_PAIR(h+2));
            mvwprintw(w,7,47,"               ");
            mvwprintw(w,2,47,"%s",choices[h]);
            wattroff(w,COLOR_PAIR(h+2));
            choice = wgetch(w);

            switch (choice) {
            case KEY_UP:
                h = (h-1) % 5;
                if (h<0) h = 4;
                break;

            case KEY_DOWN:
                h = (h+1) % 5;
                break;
            
            default:
                break;
            }

            
        } while (choice != 10);

        card->Incan = h;
    }
}

FL_POWER_WORD ReadPowerWord(WINDOW* w) {
    
    wclear(w);
    box(w,0,0);

    mvwprintw(w,1,1,"Select your Power word: ");
    const char* PowerWords[] = {"DEAL","MEND","INFLICT","DISPEL","SUMMON","IMMUNE"};
    int h = CreateSimpleMenu(w,PowerWords,6,25,1);
    FL_POWER_NAMES type = h;

    switch (type) {

        case DEAL:

        break;

        case MEND:
        
        break;

        case INFLICT:
        
        break;

        case SUMMON:
        
        break;

        case IMMUNE:
        
        break;




    }


}

FL_CARD NewCard(WINDOW* w, FL_CARD_TYPE t) {

    FL_CARD Card;

    for (int i=0; i<3; i++) {
        CreateInputWindow(w,t,i+1);
        ReadInputWindow(w,&Card.Card[i],t);
        Card.Card[i].pw1 = ReadPowerWord(w);

    }


    return Card;



}

