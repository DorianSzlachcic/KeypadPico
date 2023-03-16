add_library(FileSystem filesystem.h filesystem.c)

target_link_libraries(FileSystem PUBLIC pico_stdlib hardware_flash lfs)