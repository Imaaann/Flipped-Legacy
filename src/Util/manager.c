#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

// Adds a Static Object to the managaer based on a code and a pre-set hash map of init functions
GameObj* manager_addObject(manager* self ,Uint16 code, SDL_Renderer* ren, StaticInitFunc static_objs[]) {
    if (code > MAX_GLOBAL_OBJS) {
        perror("Code too big!\n");
        return NULL;
    }

    StaticInitFunc init_obj = static_objs[code];
    GameObj* tmp = init_obj(ren);

    self->Static[self->StaticCtr] = tmp;
    self->StaticCtr++;

    return tmp;
}

// Adds an Interactive Object to the manager based on a code and a pre-set hash map of init functions
IntGameObj* manager_addIntObject(manager* self ,Uint16 code, SDL_Renderer* ren, IntInitFunc inter_objs[]) {
    if (code > MAX_GLOBAL_OBJS) {
        perror("Code too big!\n");
        return NULL;
    }

    IntInitFunc init_obj = inter_objs[code];
    IntGameObj* tmp = init_obj(ren);

    self->Inter[self->IntCtr] = tmp;
    self->IntCtr++;

    return tmp;
}

// Removes an Object from the manager using a flag (1 = Interactive | 0 = Static) and free's it from the heap
void manager_removeObject(manager* self, int ID, int isInter) {
    int location = -1;

    if (!isInter) {

        //search in Static Array
        location = search_static(self->Static,ID,MAX_MANAGER_STATIC_OBJ);
        if (location == -1) {
            perror("object not found!\n");
            return;
        }

        // find pointer and set to Null
        GameObj* tmp = self->Static[location];
        self->Static[location] = NULL;

        // free the object
        free(tmp);

        // compress Static array so No holes
        compress_static(self->Static,MAX_MANAGER_STATIC_OBJ);

        // Decrease the static counter
        self->StaticCtr--;

} else {

        // search In Inter Array
        location = search_inter(self->Inter,ID,MAX_MANAGER_INTER_OBJ);
        if (location == -1) {
            perror("object not found!\n");
            return;
        }

        // find pointer and set to Null
        IntGameObj* tmp = self->Inter[location];
        self->Inter[location] = NULL;

        // free the object
        free(tmp);

        // compress Inter array so No holes
        compress_inter(self->Inter,MAX_MANAGER_INTER_OBJ);

        // Decrease the Inter counter
        self->IntCtr--;
    }
}

// Updates all the objects hosted by the manager
void manager_updateAll(manager* self) {

    for (int i = 0; i<self->StaticCtr; i++) {
        if (self->Static[i] != NULL) {
            self->Static[i]->update(self->Static[i]);
        }
    }

    for (int i = 0; i<self->IntCtr; i++) {
        if (self->Inter[i] != NULL) {
            self->Inter[i]->update(self->Inter[i]);
        }
    }

    printf("\n[LOG] Manager Full -U Rotation Done!\n");
}

// Renders all the objects hosted by the manager
void manager_renderAll(manager* self, SDL_Renderer* ren) {
    for (int i = 0; i<self->StaticCtr; i++) {
        if (self->Static[i] != NULL) {
            self->Static[i]->render(self->Static[i], ren);
        }
    }

    for (int i = 0; i<self->IntCtr; i++) {
        if (self->Inter[i] != NULL) {
            self->Inter[i]->render(self->Inter[i], ren);
        }
    }
}

// Checks for event hits with all interactive objects
void manager_checkAll(manager* self, SDL_Event e, game_state* data, StaticInitFunc Statics[], IntInitFunc Inter[]) {
    for (int i = 0; i<self->IntCtr; i++) {
        if (self->Inter[i] != NULL) {
            self->Inter[i]->effect(self->Inter[i], e,data,Statics,Inter);
        }
    }
} 

// Clears all the objects inside the arrays
void manager_clear(manager* self) {
    GameObj* Stmp = NULL;
    IntGameObj* Itmp = NULL;
    for (int i=0; i<MAX_MANAGER_STATIC_OBJ; i++) {

        if (i<MAX_MANAGER_INTER_OBJ) {
            Itmp = self->Inter[i];
            self->Inter[i] = NULL;
            free(Itmp);
        }

        Stmp = self->Static[i];
        self->Static[i] = NULL;
        free(Stmp);

    }

    self->IntCtr = 0;
    self->StaticCtr = 0;
}

//initializes a manager insteace using all the functions stated before
void manager_init(manager* m) {
    m->StaticCtr = 0;
    m->IntCtr = 0;

    for (int i = 0; i<MAX_MANAGER_STATIC_OBJ; i++) {
        if (i<MAX_MANAGER_INTER_OBJ) {
            m->Inter[i] = NULL;
        }

        m->Static[i] = NULL; 
    }

    m->addIntObject = manager_addIntObject;
    m->addObject = manager_addObject;
    m->removeObject = manager_removeObject;

    
    m->updateAll = manager_updateAll;
    m->renderAll = manager_renderAll;
    m->clear = manager_clear;

    m->checkAll = manager_checkAll;
}
