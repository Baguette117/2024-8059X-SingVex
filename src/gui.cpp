#include "main.h"

autonPaths selectedPath;

lv_obj_t *buttonMatrix, *pathLabel;

static void buttonMatrixEventListener(lv_event_t* e) {


    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = (lv_obj_t *)lv_event_get_target(e);
    uint32_t id;
    if (code == LV_EVENT_VALUE_CHANGED) {
        id = lv_btnmatrix_get_selected_btn(obj);
    }

    switch (id) {
        case 0:
            lv_label_set_text(pathLabel, "calibration");
            selectedPath = calibrationPath;
            break;
        case 1:
            lv_label_set_text(pathLabel, "redFar");
            selectedPath = redFar;
            break;
        case 2:
            lv_label_set_text(pathLabel, "redNear");
            selectedPath = redNear;
            break;
        case 3:
            lv_label_set_text(pathLabel, "redAWP");
            selectedPath = redAWP;
            break;
        case 4:
            lv_label_set_text(pathLabel, "skills");
            selectedPath = skillsPath;
            break;
        case 5:
            lv_label_set_text(pathLabel, "blueFar");
            selectedPath = blueFar;
            break;
        case 6:
            lv_label_set_text(pathLabel, "blueNear");
            selectedPath = blueNear;
            break;
        case 7:
            lv_label_set_text(pathLabel, "blueAWP");
            selectedPath = blueAWP;
            break;
    }

    return;
}

void initButtonMatrix(void) {
    // Create a button descriptor string array w/ no repeat "\224"
    static const char* buttonMap[] = {
        "calibration", "redFar", "redNear", "redAWP", "\n",
        "skills", "blueFar", "blueNear", "blueAWP", NULL };

    // Create a default button matrix* no repeat
    buttonMatrix = lv_btnmatrix_create(lv_scr_act());
    lv_obj_set_size(buttonMatrix, lv_obj_get_width(lv_scr_act()), lv_obj_get_height(lv_scr_act()) - 32);
    lv_obj_set_style_text_font(buttonMatrix, LV_FONT_MONTSERRAT_38, 1);
    lv_btnmatrix_set_map(buttonMatrix, buttonMap);
    lv_obj_align(buttonMatrix, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_add_event_cb(buttonMatrix, buttonMatrixEventListener, LV_EVENT_VALUE_CHANGED, NULL);

    pathLabel = lv_label_create(lv_scr_act());
    lv_label_set_text(pathLabel, "Select a path");
    lv_obj_align(pathLabel, LV_ALIGN_TOP_MID, 0, 0);
}