#include "fl-word.h"
#include "fl-condition/fl-condition.h"
#include "fl-power-word/fl-power-word.h"
#include <utils.h>

void fl_card_get_word_input(FLWord* word, WINDOW* input, int word_num) {
    mvwprintw(input, 0, 0, "Word %d", word_num);
    fl_condition_input(&word->condition, input);
    fl_power_input(&word->power, input);
}
