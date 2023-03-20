add_library(Display display.h display.c)

include_directories(../../lib/Config)
include_directories(../../lib/e-Paper)
include_directories(../../lib/GUI)
include_directories(../img)

target_link_libraries(Display PUBLIC ePaper GUI Config pico_stdlib hardware_spi Img)