SET(SOURCES screens/ui_IntroScreen.c
    screens/ui_WifiScreen.c
    screens/ui_MeasurementsScreen.c
    screens/ui_AlienTicTacToe.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
<<<<<<< HEAD
    ui_events.c)
=======
    ui_events.c
    images/ui_img_1049535237.c)
>>>>>>> a1c54b8 (wifi)

add_library(ui ${SOURCES})
