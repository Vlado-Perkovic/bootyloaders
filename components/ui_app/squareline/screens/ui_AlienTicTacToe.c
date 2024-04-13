// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#include "../ui.h"

void ui_AlienTicTacToe_screen_init(void)
{
    ui_AlienTicTacToe = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_AlienTicTacToe, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_neptuncina4 = lv_img_create(ui_AlienTicTacToe);
    lv_img_set_src(ui_neptuncina4, &ui_img_1159460666);
    lv_obj_set_width(ui_neptuncina4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_neptuncina4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_neptuncina4, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_neptuncina4, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_neptuncina4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_neptuncina4, 600);

    ui_Button13 = lv_btn_create(ui_AlienTicTacToe);
    lv_obj_set_width(ui_Button13, 100);
    lv_obj_set_height(ui_Button13, 50);
    lv_obj_set_x(ui_Button13, -101);
    lv_obj_set_y(ui_Button13, -88);
    lv_obj_set_align(ui_Button13, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Button13, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button13, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_add_event_cb(ui_Button13, ui_event_Button13, LV_EVENT_ALL, NULL);

}
