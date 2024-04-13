idf_component_register(SRCS 
"ui_app.c" 
"squareline/ui.c" 
"squareline/ui_helpers.c" 
"squareline/ui_events.c"
"squareline/components/ui_comp_button1.c"
"squareline/components/ui_comp.c"
"squareline/components/ui_comp_hook.c"
"squareline/screens/ui_MainScreen.c"
"squareline/screens/ui_mapScreen.c"
"squareline/screens/ui_ProvisionScreen.c"
"squareline/screens/ui_endGameScreen.c"
INCLUDE_DIRS "" "squareline" "squareline/components"
REQUIRES lvgl lvgl_esp32_drivers wifi game led button joystick telemetry)

# idf_component_register(SRCS "ui_app.c" "squareline/ui.c" "squareline/ui_helpers.c"
# INCLUDE_DIRS "" "squareline" "squareline/components"
# REQUIRES lvgl lvgl_esp32_drivers)
# add_subdirectory(squareline)