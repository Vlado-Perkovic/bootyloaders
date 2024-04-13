// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#include "ui_helpers.h"
#include "ui_events.h"

// SCREEN: ui_IntroScreen
void ui_IntroScreen_screen_init(void);
extern lv_obj_t * ui_IntroScreen;
void ui_event_ReadMeasurements(lv_event_t * e);
extern lv_obj_t * ui_ReadMeasurements;
void ui_event_Challenge(lv_event_t * e);
extern lv_obj_t * ui_Challenge;
void ui_event_WifiSettings(lv_event_t * e);
extern lv_obj_t * ui_WifiSettings;
extern lv_obj_t * ui_Wifi_Settings;
extern lv_obj_t * ui_Station_Sensors;
extern lv_obj_t * ui_Fight_an_Alien;
extern lv_obj_t * ui_Label9;
// SCREEN: ui_WifiScreen
void ui_WifiScreen_screen_init(void);
void ui_event_WifiScreen(lv_event_t * e);
extern lv_obj_t * ui_WifiScreen;
void ui_event_Button8(lv_event_t * e);
extern lv_obj_t * ui_Button8;
void ui_event_WifiConnectButton(lv_event_t * e);
extern lv_obj_t * ui_WifiConnectButton;
void ui_event_BackHome(lv_event_t * e);
extern lv_obj_t * ui_BackHome;
extern lv_obj_t * ui_BackFromWifi;
extern lv_obj_t * ui_WIfiAvailability;
extern lv_obj_t * ui_WifiAvailability;
// SCREEN: ui_MeasurementsScreen
void ui_MeasurementsScreen_screen_init(void);
extern lv_obj_t * ui_MeasurementsScreen;
extern lv_obj_t * ui_TempSensing;
extern lv_obj_t * ui_HumSensing;
extern lv_obj_t * ui_AccSensing;
extern lv_obj_t * ui_T;
extern lv_obj_t * ui_H;
extern lv_obj_t * ui_Acc;
void ui_event_BackToHome(lv_event_t * e);
extern lv_obj_t * ui_BackToHome;
void ui_event_Back(lv_event_t * e);
extern lv_obj_t * ui_Back;
// SCREEN: ui_AlienTicTacToe
void ui_AlienTicTacToe_screen_init(void);
extern lv_obj_t * ui_AlienTicTacToe;
void ui_event_Button13(lv_event_t * e);
extern lv_obj_t * ui_Button13;
void ui_event____initial_actions0(lv_event_t * e);
extern lv_obj_t * ui____initial_actions0;


void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
