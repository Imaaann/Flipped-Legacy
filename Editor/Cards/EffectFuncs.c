#include "../EditorTypes.h"
#include <stdio.h>
void Invisibility(FL_ROUND_PACKET round_packet) {
    FL_Character* Eff_Char[3] = {NULL};
    FL_ENEMY* Eff_Enem[3] = {NULL};

    for (int i=0; i<3; i++) {
        if(round_packet.Character[i]->active->type == INVISIBILITY) {
            Eff_Char[i] = round_packet.Character[i];
        }
        if(round_packet.Enemies[i]->active->type == INVISIBILITY) {
            Eff_Char[i] = round_packet.Enemies[i];
        }
    }





    int i;
    for (i = 0; i < 3; i++) {
        if (round_packet.Effected_Char[i] == 1) {
            round_packet.Character[i]->DEF = (round_packet.Character[i]->DEF+1)*10000; // Set DEF to a very high value to make them immune to physical damage
        }
        if (round_packet.Effected_Enem[i] == 1) {
            round_packet.Enemies[i]->DEF = (round_packet.Enemies[i]->DEF+1)*10000; // Set DEF to a very high value to make them immune to physical damage
        }
    }
}