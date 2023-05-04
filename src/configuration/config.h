#pragma once

struct button
{
    char type; // 'k' for keyboard report, 'c' for consumer report
    char modifiers; // if type=='k', else -1
    char keycode[6]; // if type=='k', else {-1, -1, -1, -1, -1, -1}
    int consumer_report; // if type=='c', else -1
};

struct config
{
    unsigned char image_bitmap[4736];
    struct button button1;
    struct button button2;
    struct button button3;
    struct button button4;
    struct button button5;
    struct button button6;
    struct button button7;
    struct button button8;
};