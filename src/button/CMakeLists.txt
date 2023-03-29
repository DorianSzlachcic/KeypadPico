add_library(Button button.h button.c)

target_link_libraries(Button PUBLIC pico_stdlib HID tinyusb_device tinyusb_board)