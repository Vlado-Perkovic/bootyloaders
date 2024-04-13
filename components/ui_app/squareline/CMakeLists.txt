SET(SOURCES components/ui_comp_button1.c
    components/ui_comp.c
    screens/ui_ProvisionScreen.c
    screens/ui_MainScreen.c
    screens/ui_mapScreen.c
    screens/ui_endGameScreen.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c)

add_library(ui ${SOURCES})
