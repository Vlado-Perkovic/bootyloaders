// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_IntroScreen
void ui_IntroScreen_screen_init(void);
lv_obj_t * ui_IntroScreen;
void ui_event_ReadMeasurements(lv_event_t * e);
lv_obj_t * ui_ReadMeasurements;
void ui_event_Challenge(lv_event_t * e);
lv_obj_t * ui_Challenge;
void ui_event_WifiSettings(lv_event_t * e);
lv_obj_t * ui_WifiSettings;
lv_obj_t * ui_Wifi_Settings;
lv_obj_t * ui_Station_Sensors;
lv_obj_t * ui_Fight_an_Alien;
lv_obj_t * ui_Label9;


// SCREEN: ui_WifiScreen
void ui_WifiScreen_screen_init(void);
void ui_event_WifiScreen(lv_event_t * e);
lv_obj_t * ui_WifiScreen;
void ui_event_Button8(lv_event_t * e);
lv_obj_t * ui_Button8;
void ui_event_WifiConnectButton(lv_event_t * e);
lv_obj_t * ui_WifiConnectButton;
void ui_event_BackHome(lv_event_t * e);
lv_obj_t * ui_BackHome;
lv_obj_t * ui_;
lv_obj_t * ui_BackFromWifi;
lv_obj_t * ui_WIfiAvailability;
lv_obj_t * ui_WifiAvailability;


// SCREEN: ui_MeasurementsScreen
void ui_MeasurementsScreen_screen_init(void);
lv_obj_t * ui_MeasurementsScreen;
lv_obj_t * ui_TempSensing;
lv_obj_t * ui_HumSensing;
lv_obj_t * ui_AccSensing;
lv_obj_t * ui_T;
lv_obj_t * ui_H;
lv_obj_t * ui_Acc;
void ui_event_BackToHome(lv_event_t * e);
lv_obj_t * ui_BackToHome;
void ui_event_Back(lv_event_t * e);
lv_obj_t * ui_Back;


// SCREEN: ui_AlienTicTacToe
void ui_AlienTicTacToe_screen_init(void);
lv_obj_t * ui_AlienTicTacToe;
void ui_event_Button13(lv_event_t * e);
lv_obj_t * ui_Button13;
void ui_event____initial_actions0(lv_event_t * e);
lv_obj_t * ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_ReadMeasurements(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        btn1_clicked(e);
    }
    if(event_code == LV_EVENT_PRESSED) {
        _ui_screen_change(&ui_MeasurementsScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_MeasurementsScreen_screen_init);
    }
}
void ui_event_Challenge(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_PRESSED) {
        _ui_screen_change(&ui_AlienTicTacToe, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_AlienTicTacToe_screen_init);
    }
}
void ui_event_WifiSettings(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_WifiScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_WifiScreen_screen_init);
    }
}
void ui_event_WifiScreen(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_SCREEN_LOAD_START) {
        ui_events_is_wifi_available(e);
    }
}
void ui_event_Button8(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        start_provision(e);
    }
}
void ui_event_WifiConnectButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        connect_to_wifi(e);
    }
}
void ui_event_BackHome(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_IntroScreen, LV_SCR_LOAD_ANIM_NONE, 500, 0, &ui_IntroScreen_screen_init);
    }
}
void ui_event_BackToHome(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_IntroScreen, LV_SCR_LOAD_ANIM_NONE, 500, 0, &ui_IntroScreen_screen_init);
    }
}
void ui_event_Back(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_IntroScreen, LV_SCR_LOAD_ANIM_NONE, 500, 0, &ui_IntroScreen_screen_init);
    }
}
void ui_event_Button13(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_IntroScreen, LV_SCR_LOAD_ANIM_NONE, 500, 0, &ui_IntroScreen_screen_init);
    }
}
void ui_event____initial_actions0(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_SCREEN_LOAD_START) {
        ui_setup(e);
    }
}

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_IntroScreen_screen_init();
    ui_WifiScreen_screen_init();
    ui_MeasurementsScreen_screen_init();
    ui_AlienTicTacToe_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_obj_add_event_cb(ui____initial_actions0, ui_event____initial_actions0, LV_EVENT_ALL, NULL);

    lv_disp_load_scr(ui____initial_actions0);
    lv_disp_load_scr(ui_IntroScreen);
}
