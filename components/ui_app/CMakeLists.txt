idf_component_register(SRCS 
"ui_app.c" 
"squareline/ui.c" 
"squareline/ui_events.c" 
"squareline/ui_helpers.c" 
"squareline/components/ui_comp_hook.c"
"squareline/screens/ui_IntroScreen.c"
"squareline/screens/ui_AlienTicTacToe.c"
"squareline/screens/ui_MeasurementsScreen.c"
"squareline/screens/ui_WifiScreen.c"
"squareline/images/ui_img_neptune_png.c"
INCLUDE_DIRS "" "squareline" "squareline/components"
REQUIRES lvgl lvgl_esp32_drivers wifi game led button joystick telemetry sensor)

# idf_component_register(SRCS "ui_app.c" "squareline/ui.c" "squareline/ui_helpers.c"
# INCLUDE_DIRS "" "squareline" "squareline/components"
# REQUIRES lvgl lvgl_esp32_drivers)
# add_subdirectory(squareline)
