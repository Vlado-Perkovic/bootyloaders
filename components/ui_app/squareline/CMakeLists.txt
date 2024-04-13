SET(SOURCES screens/ui_IntroScreen.c
    screens/ui_WifiScreen.c
    screens/ui_MeasurementsScreen.c
    screens/ui_AlienTicTacToe.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_1159460666.c)

add_library(ui ${SOURCES})
