#pragma once

// Keyboard report
void send_keyboard_report(unsigned char modifiers, unsigned char keycode[]);

// Consumer report
void send_consumer_report(int consumer_report, unsigned int len);
