set(COMPONENT_SRCS "telemetry.c" "platform/src/telemetry_driver.c")
set(COMPONENT_ADD_INCLUDEDIRS "platform/inc" ".")
set(COMPONENT_REQUIRES freertos esp_event mqtt esp_system)

register_component()