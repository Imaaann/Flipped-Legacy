#include <stdio.h>
#include <stdlib.h>


void swapS(GameObj** p1,GameObj** p2) {
    GameObj* p_tmp;
    p_tmp = *p1;
    *p1 = *p2;
    *p2 = p_tmp;
}

void swapI(IntGameObj** p1,IntGameObj** p2) {
    IntGameObj* p_tmp;
    p_tmp = *p1;
    *p1 = *p2;
    *p2 = p_tmp;
}

int search_static(GameObj** arr, int ID, int n) {

    for (int i=0; i<n; i++) {
        if (arr[i]->ID == ID) {
            return i;
        }
    }

    return -1;
}

// This function assumes 1 NULL pointer that isnt at the end
void compress_static(GameObj** arr, int n) {

    for (int i = 0; i<(n-1) ; i++) {
        if (arr[i] == NULL) {
            swapS(&arr[i],&arr[i+1]);
        }
    }

}

int search_inter(IntGameObj** arr, int ID, int n) {

    for (int i=0; i<n; i++) {
        if (arr[i]->ID == ID) {
            return i;
        }
    }

    return -1;
}

// This function assumes 1 NULL pointer that isnt at the end
void compress_inter(IntGameObj** arr, int n) {

    for (int i = 0; i<(n-1) ; i++) {
        if (arr[i] == NULL) {
            swapI(&arr[i],&arr[i+1]);
        }
    }

}
