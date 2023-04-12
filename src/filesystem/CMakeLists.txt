add_library(Filesystem filesystem.h filesystem.c)

target_link_libraries(Filesystem PUBLIC pico_stdlib hardware_flash lfs)