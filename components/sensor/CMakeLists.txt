set(COMPONENT_SRCS "sensor.c platform/src/sht3x.c platform/src/lis3dh.c platform/src/esp8266_wrapper.c")
set(COMPONENT_ADD_INCLUDEDIRS "" "." "platform/inc")
set(COMPONENT_REQUIRES driver freertos)

register_component()
