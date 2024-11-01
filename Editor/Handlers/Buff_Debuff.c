#include "../EditorTypes.h"
#include <stdio.h>

void StatsManipulator(FL_STATS stat1 , FL_STATS stat2 , int mult1 , int mult2 , FL_ROUND_PACKET round_packet){
    int i;

    switch (stat1){
        case 0:
            for(i=0 ; i<3 ; i++){
                if(round_packet.Effected_Enem[i] == 1){
                round_packet.Enemies[i]->HP.MAX_HP += mult1;
                }
            }
            for(i=0 ; i<3 ; i++){
                if(round_packet.Effected_Char[i] == 1){
                round_packet.Character[i]->HP.MAX_HP += mult1;
                }
            }
            break;
        case 1:
            for(i=0 ; i<3 ; i++){
                if(round_packet.Effected_Enem[i] == 1){
                round_packet.Enemies[i]->ATK += mult1;
                }
            }
            for(i=0 ; i<3 ; i++){
                if(round_packet.Effected_Char[i] == 1){
                round_packet.Character[i]->ATK += mult1;
                }
            }
            break;
        case 2:
            for(i=0 ; i<3 ; i++){
                if(round_packet.Effected_Enem[i] == 1){
                round_packet.Enemies[i]->DEF += mult1;
                }
            }
            for(i=0 ; i<3 ; i++){
                if(round_packet.Effected_Char[i] == 1){
                round_packet.Character[i]->DEF += mult1;
                }
            }
            break;
        case 3:
            for(i=0 ; i<3 ; i++){
                if(round_packet.Effected_Enem[i] == 1){
                round_packet.Enemies[i]->RES += mult1;
                }
            }
            for(i=0 ; i<3 ; i++){
                if(round_packet.Effected_Char[i] == 1){
                round_packet.Character[i]->RES += mult1;
                }
            }
            break;
        case 4:
            for(i=0 ; i<3 ; i++){
                if(round_packet.Effected_Enem[i] == 1){
                round_packet.Enemies[i]->SPD += mult1;
                }
            }
            for(i=0 ; i<3 ; i++){
                if(round_packet.Effected_Char[i] == 1){
                round_packet.Character[i]->SPD += mult1;
                }
            }
            break;

        default:
            break;
     }

     switch (stat2){
        case 0:
            for(i=0 ; i<3 ; i++){
                if(round_packet.Effected_Enem[i] == 1){
                round_packet.Enemies[i]->HP.MAX_HP += mult1;
                }
            }
            for(i=0 ; i<3 ; i++){
                if(round_packet.Effected_Char[i] == 1){
                round_packet.Character[i]->HP.MAX_HP += mult1;
                }
            }
            break;
        case 1:
            for(i=0 ; i<3 ; i++){
                if(round_packet.Effected_Enem[i] == 1){
                round_packet.Enemies[i]->ATK += mult1;
                }
            }
            for(i=0 ; i<3 ; i++){
                if(round_packet.Effected_Char[i] == 1){
                round_packet.Character[i]->ATK += mult1;
                }
            }
            break;
        case 2:
            for(i=0 ; i<3 ; i++){
                if(round_packet.Effected_Enem[i] == 1){
                round_packet.Enemies[i]->DEF += mult1;
                }
            }
            for(i=0 ; i<3 ; i++){
                if(round_packet.Effected_Char[i] == 1){
                round_packet.Character[i]->DEF += mult1;
                }
            }
            break;
        case 3:
            for(i=0 ; i<3 ; i++){
                if(round_packet.Effected_Enem[i] == 1){
                round_packet.Enemies[i]->RES += mult1;
                }
            }
            for(i=0 ; i<3 ; i++){
                if(round_packet.Effected_Char[i] == 1){
                round_packet.Character[i]->RES += mult1;
                }
            }
            break;
        case 4:
            for(i=0 ; i<3 ; i++){
                if(round_packet.Effected_Enem[i] == 1){
                round_packet.Enemies[i]->SPD += mult1;
                }
            }
            for(i=0 ; i<3 ; i++){
                if(round_packet.Effected_Char[i] == 1){
                round_packet.Character[i]->SPD += mult1;
                }
            }
            break;

        default:
            break;
     }    
}
void Riot(){
}

void Reflect(){}

void Energy_Siphon(FL_ROUND_PACKET round_packet){
    FL_Character* Eff_Char[3] = {NULL};
    FL_ENEMY* Eff_Enem[3] = {NULL};

    for (int i=0; i<3; i++) {
        for(int j=0;j<MAX_EFFECTS;j++){
        if(round_packet.Character[i]->active[j].type == ENERGY_SYPHON) {
            Eff_Char[i] = round_packet.Character[i];
        }
        if(round_packet.Enemies[i]->active[j].type == ENERGY_SYPHON) {
            Eff_Char[i] = round_packet.Enemies[i];
        }}
    }

    for(int i=0;i<3;i++){
        if(Eff_Char[i] != NULL){
            Eff_Char[i]->SP.CURRENT_SP += 1;
        }
        if(Eff_Enem[i] != NULL){
            Eff_Enem[i]->SP.CURRENT_SP += 1;
        }
        
    }
}

void Invisibility(FL_ROUND_PACKET round_packet) {
    FL_Character* Eff_Char[3] = {NULL};
    FL_ENEMY* Eff_Enem[3] = {NULL};

    for (int i=0; i<3; i++) {
        for(int j=0;j<MAX_EFFECTS;j++){
        if(round_packet.Character[i]->active[j].type == INVISIBILITY) {
            Eff_Char[i] = round_packet.Character[i];
        }
        if(round_packet.Enemies[i]->active[j].type == INVISIBILITY) {
            Eff_Char[i] = round_packet.Enemies[i];
        }}
    }
    
    for (int i=0; i<3; i++) {
        if(Eff_Char[i] != NULL) {
            Eff_Char[i]->DEF= (Eff_Char[i]->DEF + 1)*10000;
        }
        if(Eff_Enem[i] != NULL) {
            Eff_Enem[i]->DEF= (Eff_Enem[i]->DEF + 1)*10000;
        }
    }}

void Barrier(FL_ROUND_PACKET round_packet , int x) {
    FL_Character* Eff_Char[3] = {NULL};
    FL_ENEMY* Eff_Enem[3] = {NULL};

    for (int i=0; i<3; i++) {
        for(int j=0;j<MAX_EFFECTS;j++){
        if(round_packet.Character[i]->active[j].type == BARRIER) {
            Eff_Char[i] = round_packet.Character[i];
        }
        if(round_packet.Enemies[i]->active[j].type == BARRIER) {
            Eff_Char[i] = round_packet.Enemies[i];
        }}
    }
    for(int i=0 ; i<3; i++){
        if(Eff_Char[i] != NULL){
            Eff_Char[i]->HP.CURRENT_HP += x;
        }
        if(Eff_Enem[i] != NULL){
            Eff_Enem[i]->HP.CURRENT_HP += x;
        }
    }
}

void Inspiritation(FL_ROUND_PACKET round_packet) {
    
}

void Arcane_Stemp(FL_ROUND_PACKET round_packet) {
    FL_Character* Eff_Char[3] = {NULL};
    FL_ENEMY* Eff_Enem[3] = {NULL};

    for (int i=0; i<3; i++) {
        for(int j=0;j<MAX_EFFECTS;j++){
        if(round_packet.Character[i]->active[j].type == ARCANE_STEMP) {
            Eff_Char[i] = round_packet.Character[i];
        }
        if(round_packet.Enemies[i]->active[j].type == ARCANE_STEMP) {
            Eff_Char[i] = round_packet.Enemies[i];
        }}
    }
    for(int i=0 ; i<3; i++){
        if(Eff_Char[i] != NULL){
            for(int j=0;j<MAX_EFFECTS;j++){
                if(Eff_Char[i]->active[j].type != NO_EFFECT){
                    Eff_Char[i]->active[j].rounds_left += 1;
                }
            }
        }
        if(Eff_Enem[i] != NULL){
            for(int j=0;j<MAX_EFFECTS;j++){
                if(Eff_Enem[i]->active[j].type != NO_EFFECT){
                    Eff_Enem[i]->active[j].rounds_left += 1;
                }
            }
        }

    }
}

