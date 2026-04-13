#include QMK_KEYBOARD_H

#ifdef OLED_ENABLE

static const char* layer_name(void) {
    switch (get_highest_layer(layer_state)) {
        case 0: return "SKETCHER ";
        case 1: return "CONSTRNTS";
        case 2: return "NUMPAD   ";
        case 3: return "PART DES ";
        case 4: return "CTRL ";
        default: return "?????????";
    }
}

static const char* layer_hint(void) {
    switch (get_highest_layer(layer_state)) {
        case 0: return "X F T P R";
        case 1: return "          SYM";
        case 2: return "9 8 7 6 5";
        case 3: return "Pad Pkt Rev Flt Chm";
        case 4: return "Cut Cpy Paste Undo F2";
        default: return "";
    }
}

static const char* layer_hint2(void) {
    switch (get_highest_layer(layer_state)) {
        case 0: return "X A . H L";
        case 1: return "Coin  A   HV   EQ TNG";
        case 2: return "4 3 2 1 0";
        case 3: return "Pad Pkt Rev Flt Chm";
        case 4: return "              Redo   ";
        default: return "";
    }
}

static const char* layer_hint3(void) {
    switch (get_highest_layer(layer_state)) {
        case 0: return "L A C S P";
        case 1: return " ||   POL COIN |_";
        case 2: return "< * / . >";
        case 3: return "Pad Pkt Rev Flt Chm";
        case 4: return "";
        default: return "";
    }
}

bool oled_task_user(void) {
    static uint8_t last_layer = 255;
    uint8_t current_layer = get_highest_layer(layer_state);
    
    if (current_layer != last_layer) {
        last_layer = current_layer;
        oled_clear();

        oled_set_cursor(0, 0);
        oled_write_P(PSTR("Layer: "), false);
        oled_write(layer_name(), false);

        oled_set_cursor(0, 1);
        oled_write(layer_hint(), false);

        oled_set_cursor(0, 2);
        oled_write(layer_hint2(), false);

        oled_set_cursor(0, 3);
        oled_write(layer_hint3(), false);
    }

    return false;
}

#endif