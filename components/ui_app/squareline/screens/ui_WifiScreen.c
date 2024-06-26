// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#include "../ui.h"

void ui_WifiScreen_screen_init(void)
{
ui_WifiScreen = lv_obj_create(NULL);
lv_obj_clear_flag( ui_WifiScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_WifiScreen, lv_color_hex(0x0F7AC0), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_WifiScreen, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Button8 = lv_btn_create(ui_WifiScreen);
lv_obj_set_width( ui_Button8, 125);
lv_obj_set_height( ui_Button8, 35);
lv_obj_set_x( ui_Button8, 94 );
lv_obj_set_y( ui_Button8, -97 );
lv_obj_set_align( ui_Button8, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Button8, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_Button8, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Button8, lv_color_hex(0x6B696F), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Button8, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ProvisionLabel = lv_label_create(ui_Button8);
lv_obj_set_width( ui_ProvisionLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ProvisionLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_ProvisionLabel, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_ProvisionLabel,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_ProvisionLabel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_label_set_text(ui_ProvisionLabel,"Wi-Fi provision");

ui_WifiConnectButton = lv_btn_create(ui_WifiScreen);
lv_obj_set_width( ui_WifiConnectButton, 255);
lv_obj_set_height( ui_WifiConnectButton, 50);
lv_obj_set_x( ui_WifiConnectButton, 0 );
lv_obj_set_y( ui_WifiConnectButton, 65 );
lv_obj_set_align( ui_WifiConnectButton, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_WifiConnectButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_WifiConnectButton, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_WifiConnectButton, lv_color_hex(0x97939F), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_WifiConnectButton, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ConnectToWifiLabel = lv_label_create(ui_WifiConnectButton);
lv_obj_set_width( ui_ConnectToWifiLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ConnectToWifiLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_ConnectToWifiLabel, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_ConnectToWifiLabel,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_ConnectToWifiLabel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_label_set_text(ui_ConnectToWifiLabel,"Connect To Wi-Fi");
lv_obj_set_style_text_font(ui_ConnectToWifiLabel, &lv_font_montserrat_14, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_BackHome = lv_btn_create(ui_WifiScreen);
lv_obj_set_width( ui_BackHome, 90);
lv_obj_set_height( ui_BackHome, 35);
lv_obj_set_x( ui_BackHome, -110 );
lv_obj_set_y( ui_BackHome, -97 );
lv_obj_set_align( ui_BackHome, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_BackHome, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_BackHome, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_BackHome, lv_color_hex(0x6B696F), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_BackHome, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_BackFromWifi = lv_label_create(ui_BackHome);
lv_obj_set_width( ui_BackFromWifi, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_BackFromWifi, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_BackFromWifi, 0 );
lv_obj_set_y( ui_BackFromWifi, 1 );
lv_obj_set_align( ui_BackFromWifi, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_BackFromWifi,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_BackFromWifi, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_label_set_text(ui_BackFromWifi,"<   Back");
lv_obj_set_style_text_color(ui_BackFromWifi, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_BackFromWifi, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_BackFromWifi, &lv_font_montserrat_14, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_WIfiAvailability = lv_obj_create(ui_WifiScreen);
lv_obj_set_width( ui_WIfiAvailability, 162);
lv_obj_set_height( ui_WIfiAvailability, 50);
lv_obj_set_x( ui_WIfiAvailability, 0 );
lv_obj_set_y( ui_WIfiAvailability, -12 );
lv_obj_set_align( ui_WIfiAvailability, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_WIfiAvailability, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_WifiAvailability = lv_label_create(ui_WIfiAvailability);
lv_obj_set_width( ui_WifiAvailability, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_WifiAvailability, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_WifiAvailability, LV_ALIGN_CENTER );
lv_label_set_text(ui_WifiAvailability,"");
lv_obj_set_style_text_font(ui_WifiAvailability, &lv_font_montserrat_14, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_Button8, ui_event_Button8, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_WifiConnectButton, ui_event_WifiConnectButton, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_BackHome, ui_event_BackHome, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_WifiScreen, ui_event_WifiScreen, LV_EVENT_ALL, NULL);

}
