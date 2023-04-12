add_library(HID hid.h hid.c usb_descriptors.h usb_descriptors.c tusb_config.h)

target_include_directories(HID PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(HID pico_stdlib pico_unique_id tinyusb_device tinyusb_board)