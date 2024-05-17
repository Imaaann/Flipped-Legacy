void init_StaticDictionary(StaticInitFunc dict[], int n) {

    for (int i=0; i<n; i++) {
        dict[i] = NULL;
    }

    dict[ST_GENER_IMG] = Generic_Image_Init;
    dict[ST_GENER_TXT] = Generic_TXT_Init;


}

void init_InterDictionary(IntInitFunc dict[], int n) {

    for (int i=0; i<n; i++) {
        dict[i] = NULL;
    }

    dict[INT_INVIS_JOHNCENA] = JOHNCENA_Init;
    dict[INT_GENER_BTN] = Generic_Btn_Init;
}