set(COMPONENT_SRCS "wifi.c" "platform/src/wifi_driver.c")
set(COMPONENT_ADD_INCLUDEDIRS "platform/inc" ".")
set(COMPONENT_REQUIRES esp_wifi nvs_flash freertos wifi_provisioning)

register_component()