add_library(Configuration config.h default_config.h default_config.c)

include_directories(../img)
include_directories(../button)
include_directories(../hid)

target_include_directories(Configuration PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(Configuration PUBLIC pico_stdlib tinyusb_device Img HID Button)