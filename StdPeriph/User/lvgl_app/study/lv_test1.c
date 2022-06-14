#include "lv_examples.h"
#include "lvgl.h"

void lv_study(void)
{
    lv_obj_t* label01 = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label01, "Hello, world!");
    //lv_label_set_align(label01, LV_LABEL_ALIGN_CENTER);
    lv_obj_align(label01, NULL, LV_ALIGN_CENTER, 0, 30);
    
    // lv_label_set_long_mode(label01, LV_LABEL_LONG_BREAK);     /*Break the long lines*/
    // lv_label_set_recolor(label01, true); /*Enable re-coloring by commands in the text*/
    // lv_label_set_align(label01, LV_LABEL_ALIGN_CENTER);       /*Center aligned lines*/
    // lv_label_set_text(label01, "#0000ff Re-color# #ff00ff words# #ff0000 of a# label "
    //                           "and  wrap long text automatically.");
    // lv_obj_set_width(label01, 150);
    // lv_obj_align(label01, NULL, LV_ALIGN_CENTER, 0, -30);

    // lv_obj_t * label2 = lv_label_create(lv_scr_act(), NULL);
    // lv_label_set_long_mode(label2, LV_LABEL_LONG_SROLL_CIRC);     /*Circular scroll*/
    // lv_obj_set_width(label2, 150);
    // lv_label_set_text(label2, "It is a circularly scrolling text. ");
    // lv_obj_align(label2, NULL, LV_ALIGN_CENTER, 0, 30);
}




