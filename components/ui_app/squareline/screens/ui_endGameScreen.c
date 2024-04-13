// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.4
// Project name: kraken_hunt

#include "../ui.h"

void ui_endGameScreen_screen_init(void)
{
ui_endGameScreen = lv_obj_create(NULL);
lv_obj_clear_flag( ui_endGameScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_gameResultPanel = lv_obj_create(ui_endGameScreen);
lv_obj_set_width( ui_gameResultPanel, 200);
lv_obj_set_height( ui_gameResultPanel, 100);
lv_obj_set_align( ui_gameResultPanel, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_gameResultPanel,LV_FLEX_FLOW_ROW);
lv_obj_set_flex_align(ui_gameResultPanel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_gameResultPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_gameResultLabel = lv_label_create(ui_gameResultPanel);
lv_obj_set_width( ui_gameResultLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_gameResultLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_gameResultLabel, LV_ALIGN_CENTER );

}