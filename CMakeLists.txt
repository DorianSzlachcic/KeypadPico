cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)

project(KeypadPico)
pico_sdk_init()

# add a compilation subdirectory
add_subdirectory(lib/Config)
add_subdirectory(lib/e-Paper)
add_subdirectory(lib/Fonts)
add_subdirectory(lib/GUI)

# add a header directory
include_directories(./lib/Config)
include_directories(./lib/e-Paper)
include_directories(./lib/GUI)

# generate an executable file
add_executable(KeypadPico 
main.c
)

# enable usb output, disable uart output
pico_enable_stdio_usb(KeypadPico 1)
pico_enable_stdio_uart(KeypadPico 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(KeypadPico)

target_link_libraries(KeypadPico ePaper GUI Fonts Config pico_stdlib hardware_spi)