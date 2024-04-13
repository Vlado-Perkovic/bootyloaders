set(COMPONENT_SRCS "joystick.c" "platform/src/potentiometer.c")
set(COMPONENT_ADD_INCLUDEDIRS "platform/inc" ".")
set(COMPONENT_REQUIRES esp_adc esp_event)

register_component()