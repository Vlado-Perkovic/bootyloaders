// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#include "../ui.h"

void ui_IntroScreen_screen_init(void)
{
    ui_IntroScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_IntroScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ReadMeasurements = lv_btn_create(ui_IntroScreen);
    lv_obj_set_width(ui_ReadMeasurements, 125);
    lv_obj_set_height(ui_ReadMeasurements, 35);
    lv_obj_set_x(ui_ReadMeasurements, 93);
    lv_obj_set_y(ui_ReadMeasurements, -97);
    lv_obj_set_align(ui_ReadMeasurements, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ReadMeasurements, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ReadMeasurements, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ReadMeasurements, lv_color_hex(0x6B696F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ReadMeasurements, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Challenge = lv_btn_create(ui_IntroScreen);
    lv_obj_set_width(ui_Challenge, 200);
    lv_obj_set_height(ui_Challenge, 50);
    lv_obj_set_x(ui_Challenge, 0);
    lv_obj_set_y(ui_Challenge, 72);
    lv_obj_set_align(ui_Challenge, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Challenge, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Challenge, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Challenge, lv_color_hex(0x74AD83), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Challenge, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WifiSettings = lv_btn_create(ui_IntroScreen);
    lv_obj_set_width(ui_WifiSettings, 115);
    lv_obj_set_height(ui_WifiSettings, 35);
    lv_obj_set_x(ui_WifiSettings, -97);
    lv_obj_set_y(ui_WifiSettings, -97);
    lv_obj_set_align(ui_WifiSettings, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_WifiSettings, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_WifiSettings, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_WifiSettings, lv_color_hex(0x6B696F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_WifiSettings, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Wifi_Settings = lv_label_create(ui_IntroScreen);
    lv_obj_set_width(ui_Wifi_Settings, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Wifi_Settings, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Wifi_Settings, -99);
    lv_obj_set_y(ui_Wifi_Settings, -97);
    lv_obj_set_align(ui_Wifi_Settings, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Wifi_Settings, "Wifi Settings");
    lv_obj_set_style_text_color(ui_Wifi_Settings, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Wifi_Settings, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Station_Sensors = lv_label_create(ui_IntroScreen);
    lv_obj_set_width(ui_Station_Sensors, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Station_Sensors, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Station_Sensors, 95);
    lv_obj_set_y(ui_Station_Sensors, -97);
    lv_obj_set_align(ui_Station_Sensors, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Station_Sensors, "Station Sensors");
    lv_obj_set_style_text_color(ui_Station_Sensors, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Station_Sensors, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Fight_an_Alien = lv_label_create(ui_IntroScreen);
    lv_obj_set_width(ui_Fight_an_Alien, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Fight_an_Alien, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Fight_an_Alien, -3);
    lv_obj_set_y(ui_Fight_an_Alien, 72);
    lv_obj_set_align(ui_Fight_an_Alien, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Fight_an_Alien, "Challenge the Alien");
    lv_obj_set_style_text_color(ui_Fight_an_Alien, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Fight_an_Alien, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label9 = lv_label_create(ui_IntroScreen);
    lv_obj_set_width(ui_Label9, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label9, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label9, 8);
    lv_obj_set_y(ui_Label9, -15);
    lv_obj_set_align(ui_Label9, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label9, "Wilkommen");

    lv_obj_add_event_cb(ui_ReadMeasurements, ui_event_ReadMeasurements, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Challenge, ui_event_Challenge, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_WifiSettings, ui_event_WifiSettings, LV_EVENT_ALL, NULL);

}
