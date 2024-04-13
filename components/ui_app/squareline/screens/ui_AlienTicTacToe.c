// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#include "../ui.h"

void ui_AlienTicTacToe_screen_init(void)
{
    ui_AlienTicTacToe = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_AlienTicTacToe, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ReadMeasurements1 = lv_btn_create(ui_AlienTicTacToe);
    lv_obj_set_width(ui_ReadMeasurements1, 100);
    lv_obj_set_height(ui_ReadMeasurements1, 50);
    lv_obj_set_x(ui_ReadMeasurements1, 100);
    lv_obj_set_y(ui_ReadMeasurements1, -87);
    lv_obj_set_align(ui_ReadMeasurements1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ReadMeasurements1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ReadMeasurements1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Challenge1 = lv_btn_create(ui_AlienTicTacToe);
    lv_obj_set_width(ui_Challenge1, 208);
    lv_obj_set_height(ui_Challenge1, 50);
    lv_obj_set_x(ui_Challenge1, -7);
    lv_obj_set_y(ui_Challenge1, 67);
    lv_obj_set_align(ui_Challenge1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Challenge1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Challenge1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Challenge1, lv_color_hex(0x0EE760), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Challenge1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WifiSettings1 = lv_btn_create(ui_AlienTicTacToe);
    lv_obj_set_width(ui_WifiSettings1, 100);
    lv_obj_set_height(ui_WifiSettings1, 50);
    lv_obj_set_x(ui_WifiSettings1, -102);
    lv_obj_set_y(ui_WifiSettings1, -88);
    lv_obj_set_align(ui_WifiSettings1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_WifiSettings1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_WifiSettings1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_add_event_cb(ui_ReadMeasurements1, ui_event_ReadMeasurements1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Challenge1, ui_event_Challenge1, LV_EVENT_ALL, NULL);

}