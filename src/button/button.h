#pragma once

// HID Modifiers
enum modifiers {
    NONE_MOD = 0,
    L_CTRL = 1 << 0,
    L_SHIFT = 1 << 1,
    L_ALT = 1 << 2,
    L_WIN = 1 << 3,
    R_CTRL = 1 << 4,
    R_SHIFT = 1 << 5,
    R_ALT = 1 << 6,
    R_WIN = 1 << 7,
};

// Buttons gpio pins
enum button_pins {
    BUTTON_1 = 2,
    BUTTON_2 = 3,
    BUTTON_3 = 4,
    BUTTON_4 = 5,
    BUTTON_5 = 18,
    BUTTON_6 = 19,
    BUTTON_7 = 20,
    BUTTON_8 = 21,
};

void buttons_init();
unsigned char read_buttons();
void buttons_task(unsigned char buttons_state);
