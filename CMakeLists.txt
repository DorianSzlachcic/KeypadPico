cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)

project(KeypadPico)
pico_sdk_init()

# add a compilation subdirectory
add_subdirectory(lib/Config)
add_subdirectory(lib/e-Paper)
add_subdirectory(lib/Fonts)
add_subdirectory(lib/GUI)
add_subdirectory(src/filesystem)
add_subdirectory(src/img)
add_subdirectory(src/display)
add_subdirectory(src/button)
add_subdirectory(src/hid)
add_subdirectory(src/configuration)


# add a header directory
include_directories(./lib/Config)
include_directories(./lib/e-Paper)
include_directories(./lib/GUI)
include_directories(./src/filesystem)
include_directories(./src/img)
include_directories(./src/display)
include_directories(./src/button)
include_directories(./src/hid)
include_directories(./src/configuration)


# generate an executable file
add_executable(KeypadPico 
main.c
)

# enable usb output, disable uart output
pico_enable_stdio_usb(KeypadPico 1)
pico_enable_stdio_uart(KeypadPico 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(KeypadPico)

add_library(lfs INTERFACE)
target_include_directories(lfs INTERFACE ${CMAKE_SOURCE_DIR}/thirdparty/littlefs/)
target_sources(lfs INTERFACE 
    ${CMAKE_SOURCE_DIR}/thirdparty/littlefs/lfs.h 
    ${CMAKE_SOURCE_DIR}/thirdparty/littlefs/lfs.c
    ${CMAKE_SOURCE_DIR}/thirdparty/littlefs/lfs_util.h
    ${CMAKE_SOURCE_DIR}/thirdparty/littlefs/lfs_util.c)
target_link_libraries(lfs INTERFACE pico_stdlib)

target_link_libraries(KeypadPico PUBLIC 
    ePaper
    GUI
    Fonts
    Config
    pico_stdlib
    pico_unique_id
    hardware_spi
    Img
    Display
    Button
    HID
    tinyusb_device
    tinyusb_board
    lfs
    Filesystem
    Configuration
)