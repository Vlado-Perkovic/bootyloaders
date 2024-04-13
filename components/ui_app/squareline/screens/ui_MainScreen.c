// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.4
// Project name: kraken_hunt

#include "../ui.h"

void ui_MainScreen_screen_init(void)
{
ui_MainScreen = lv_obj_create(NULL);
lv_obj_clear_flag( ui_MainScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Panel1 = lv_obj_create(ui_MainScreen);
lv_obj_set_width( ui_Panel1, 123);
lv_obj_set_height( ui_Panel1, 76);
lv_obj_set_x( ui_Panel1, 78 );
lv_obj_set_y( ui_Panel1, -66 );
lv_obj_set_align( ui_Panel1, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Panel1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label5 = lv_label_create(ui_MainScreen);
lv_obj_set_width( ui_Label5, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label5, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label5, 61 );
lv_obj_set_y( ui_Label5, -80 );
lv_obj_set_align( ui_Label5, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label5,"BOMBS 10");

ui_Label6 = lv_label_create(ui_MainScreen);
lv_obj_set_width( ui_Label6, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label6, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label6, 52 );
lv_obj_set_y( ui_Label6, -55 );
lv_obj_set_align( ui_Label6, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label6,"NETS 6");

ui_Panel3 = lv_obj_create(ui_MainScreen);
lv_obj_set_width( ui_Panel3, 81);
lv_obj_set_height( ui_Panel3, 50);
lv_obj_set_x( ui_Panel3, -57 );
lv_obj_set_y( ui_Panel3, -78 );
lv_obj_set_align( ui_Panel3, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_Panel3,LV_FLEX_FLOW_COLUMN);
lv_obj_set_flex_align(ui_Panel3, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_Panel3, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label7 = lv_label_create(ui_Panel3);
lv_obj_set_width( ui_Label7, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label7, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label7, -116 );
lv_obj_set_y( ui_Label7, -98 );
lv_obj_set_align( ui_Label7, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label7,"DIVER:");

ui_mainScreenDiverLabel = lv_label_create(ui_Panel3);
lv_obj_set_width( ui_mainScreenDiverLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_mainScreenDiverLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_mainScreenDiverLabel, -116 );
lv_obj_set_y( ui_mainScreenDiverLabel, -76 );
lv_obj_set_align( ui_mainScreenDiverLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_mainScreenDiverLabel,"Vlado");

ui_Label12 = lv_label_create(ui_MainScreen);
lv_obj_set_width( ui_Label12, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label12, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label12, 112 );
lv_obj_set_y( ui_Label12, -14 );
lv_obj_set_align( ui_Label12, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label12,"LIGHTS");

ui_Panel7 = lv_obj_create(ui_MainScreen);
lv_obj_set_width( ui_Panel7, 48);
lv_obj_set_height( ui_Panel7, 26);
lv_obj_set_x( ui_Panel7, 113 );
lv_obj_set_y( ui_Panel7, 13 );
lv_obj_set_align( ui_Panel7, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Panel7, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_mainScreenInfo = lv_obj_create(ui_MainScreen);
lv_obj_set_width( ui_mainScreenInfo, 113);
lv_obj_set_height( ui_mainScreenInfo, 144);
lv_obj_set_x( ui_mainScreenInfo, -109 );
lv_obj_set_y( ui_mainScreenInfo, 24 );
lv_obj_set_align( ui_mainScreenInfo, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_mainScreenInfo,LV_FLEX_FLOW_COLUMN);
lv_obj_set_flex_align(ui_mainScreenInfo, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
lv_obj_clear_flag( ui_mainScreenInfo, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_mainScreenInfo, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_mainScreenInfo, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_mainScreenInfo, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_mainScreenInfo, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_row(ui_mainScreenInfo, 3, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_column(ui_mainScreenInfo, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Label8 = lv_label_create(ui_mainScreenInfo);
lv_obj_set_width( ui_Label8, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label8, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label8, -120 );
lv_obj_set_y( ui_Label8, -52 );
lv_obj_set_align( ui_Label8, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label8,"SUBMARINE");
lv_obj_set_style_text_font(ui_Label8, &lv_font_montserrat_12, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Panel4 = lv_obj_create(ui_mainScreenInfo);
lv_obj_set_width( ui_Panel4, 63);
lv_obj_set_height( ui_Panel4, 20);
lv_obj_set_x( ui_Panel4, -1 );
lv_obj_set_y( ui_Panel4, -60 );
lv_obj_set_align( ui_Panel4, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_Panel4,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_Panel4, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_Panel4, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_pad_left(ui_Panel4, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_Panel4, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_Panel4, 1, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_Panel4, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_SubmarinePosition = lv_label_create(ui_Panel4);
lv_obj_set_width( ui_SubmarinePosition, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SubmarinePosition, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SubmarinePosition, 1 );
lv_obj_set_y( ui_SubmarinePosition, 2 );
lv_obj_set_align( ui_SubmarinePosition, LV_ALIGN_CENTER );
lv_label_set_text(ui_SubmarinePosition,"(10,10)");

ui_Label9 = lv_label_create(ui_mainScreenInfo);
lv_obj_set_width( ui_Label9, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label9, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label9, -123 );
lv_obj_set_y( ui_Label9, -9 );
lv_obj_set_align( ui_Label9, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label9,"DISTANCE");
lv_obj_set_style_text_font(ui_Label9, &lv_font_montserrat_12, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Panel2 = lv_obj_create(ui_mainScreenInfo);
lv_obj_set_width( ui_Panel2, 63);
lv_obj_set_height( ui_Panel2, 20);
lv_obj_set_x( ui_Panel2, 2 );
lv_obj_set_y( ui_Panel2, -27 );
lv_obj_set_align( ui_Panel2, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_Panel2,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_Panel2, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_Panel2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_DistanceFromKraken = lv_label_create(ui_Panel2);
lv_obj_set_width( ui_DistanceFromKraken, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_DistanceFromKraken, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_DistanceFromKraken, -121 );
lv_obj_set_y( ui_DistanceFromKraken, 17 );
lv_obj_set_align( ui_DistanceFromKraken, LV_ALIGN_CENTER );
lv_label_set_text(ui_DistanceFromKraken,"15 m");

ui_Label10 = lv_label_create(ui_mainScreenInfo);
lv_obj_set_width( ui_Label10, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label10, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label10, -123 );
lv_obj_set_y( ui_Label10, 34 );
lv_obj_set_align( ui_Label10, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label10,"KRAKEN");
lv_obj_set_style_text_font(ui_Label10, &lv_font_montserrat_12, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Panel5 = lv_obj_create(ui_mainScreenInfo);
lv_obj_set_width( ui_Panel5, 63);
lv_obj_set_height( ui_Panel5, 20);
lv_obj_set_x( ui_Panel5, 2 );
lv_obj_set_y( ui_Panel5, 12 );
lv_obj_set_align( ui_Panel5, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_Panel5,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_Panel5, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_Panel5, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_KrakenPosition = lv_label_create(ui_Panel5);
lv_obj_set_width( ui_KrakenPosition, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_KrakenPosition, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_KrakenPosition, LV_ALIGN_CENTER );
lv_label_set_text(ui_KrakenPosition,"(10,25)");

ui_MainScreenWeaponPanel = lv_obj_create(ui_MainScreen);
lv_obj_set_width( ui_MainScreenWeaponPanel, 166);
lv_obj_set_height( ui_MainScreenWeaponPanel, 72);
lv_obj_set_x( ui_MainScreenWeaponPanel, 52 );
lv_obj_set_y( ui_MainScreenWeaponPanel, 71 );
lv_obj_set_align( ui_MainScreenWeaponPanel, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_MainScreenWeaponPanel,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_MainScreenWeaponPanel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_MainScreenWeaponPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Button4 = lv_btn_create(ui_MainScreenWeaponPanel);
lv_obj_set_width( ui_Button4, 55);
lv_obj_set_height( ui_Button4, 55);
lv_obj_set_x( ui_Button4, 7 );
lv_obj_set_y( ui_Button4, 65 );
lv_obj_set_align( ui_Button4, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_Button4,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_Button4, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_add_flag( ui_Button4, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_Button4, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Button4, lv_color_hex(0xFF1414), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Button4, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_torpedoLabel = lv_label_create(ui_Button4);
lv_obj_set_width( ui_torpedoLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_torpedoLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_torpedoLabel, 12 );
lv_obj_set_y( ui_torpedoLabel, 72 );
lv_obj_set_align( ui_torpedoLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_torpedoLabel,"TORPEDO");
lv_obj_set_style_text_color(ui_torpedoLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_torpedoLabel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_torpedoLabel, &lv_font_montserrat_8, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Button6 = lv_btn_create(ui_MainScreenWeaponPanel);
lv_obj_set_width( ui_Button6, 40);
lv_obj_set_height( ui_Button6, 40);
lv_obj_set_x( ui_Button6, 93 );
lv_obj_set_y( ui_Button6, 75 );
lv_obj_set_align( ui_Button6, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_Button6,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_Button6, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_add_flag( ui_Button6, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_Button6, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Button6, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Button6, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_netLabel = lv_label_create(ui_Button6);
lv_obj_set_width( ui_netLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_netLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_netLabel, 60 );
lv_obj_set_y( ui_netLabel, 82 );
lv_obj_set_align( ui_netLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_netLabel,"NET");
lv_obj_set_style_text_color(ui_netLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_netLabel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_netLabel, &lv_font_montserrat_8, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Button1 = lv_btn_create(ui_MainScreenWeaponPanel);
lv_obj_set_width( ui_Button1, 40);
lv_obj_set_height( ui_Button1, 40);
lv_obj_set_x( ui_Button1, 53 );
lv_obj_set_y( ui_Button1, 75 );
lv_obj_set_align( ui_Button1, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_Button1,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_Button1, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_add_flag( ui_Button1, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_Button1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Button1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Button1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_lightLabel = lv_label_create(ui_Button1);
lv_obj_set_width( ui_lightLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_lightLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_lightLabel, LV_ALIGN_CENTER );
lv_label_set_text(ui_lightLabel,"LIGHT");
lv_obj_set_style_text_color(ui_lightLabel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_lightLabel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_lightLabel, &lv_font_montserrat_8, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_exitButton = lv_btn_create(ui_MainScreen);
lv_obj_set_width( ui_exitButton, 36);
lv_obj_set_height( ui_exitButton, 32);
lv_obj_set_x( ui_exitButton, -134 );
lv_obj_set_y( ui_exitButton, -92 );
lv_obj_set_align( ui_exitButton, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_exitButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_exitButton, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_exitButton, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_exitButton, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_Button4, ui_event_Button4, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_exitButton, ui_event_exitButton, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_MainScreen, ui_event_MainScreen, LV_EVENT_ALL, NULL);

}