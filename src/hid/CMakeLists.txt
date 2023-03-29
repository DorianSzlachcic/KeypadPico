add_library(HID hid.h hid.c usb_descriptors.h usb_descriptors.c tusb_config.h)

target_include_directories(HID PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(HID PUBLIC pico_stdlib tinyusb_device tinyusb_board)