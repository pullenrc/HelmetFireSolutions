#include QMK_KEYBOARD_H

// ── Layer indices ────────────────────────────────────────────────────
enum layers {
    L_SKETCH = 0,
    L_CONST,
    L_NUMPAD,
    L_PARTDES,
    L_CTRL
};

// ── Custom keycodes (FreeCAD macros) ─────────────────────────────────
enum custom_keycodes {
    // Sketcher draw tools
    FC_LINE = SAFE_RANGE,  // G, L - Line
    FC_CIRC,               // G, C - Circle
    FC_ARC,                // G, A    - Arc
    FC_RECT,               // G, R    - Rectangle
    FC_BSPL,               // G, B    - B-Spline
    FC_TRIM,               // T, R    - Trim
    FC_EXTD,               // T, E    - Extend
    FC_CONS,               // G, N    - Toggle construction
    FC_FITA,               // V, F    - Fit All
    FC_POLY,               // G, M    - Poly line tool, toggle types with M
    FC_FILE,               // G, F, F - fillet in sketcher workbench
    FC_PROJ,               // G, X    - External projection
    FC_HEXA,               // G, 6    - Hexagon
    FC_POIN,               // G, Y    - Point
    // Constraints (single keys, but grouped here for clarity)
    FC_COIN,               // C       - Coincident
    FC_HORZ,               // H       - Horizontal only
    FC_VERT,               // V       - Vert only
    FC_PERP,               // N       - Perpendicular
    FC_TANG,               // T       - Tangent
    FC_PARA,               // Shift+P - Parallel
    FC_PONL,               // Shift+O - Point on line
    FC_ANGL,               // K, A    - Angle
    FC_EQUL,               // E       - Equal
    FC_SYM,                // S       - Symmetry 
    FC_HV,                 // A       - Smart hor/vert
    // Part Design
    FC_PAD,                // P       - Pad
    FC_PCKT,               // Shift+P - Pocket
    FC_REVL,               // R
    FC_FILT,               // F
    FC_CHMF,               // Shift+C - Chamfer
    FC_THCK,               // Shift+T - Thickness
    FC_DRFT,               // Shift+F - Draft
};

// ── Keymap ───────────────────────────────────────────────────────────
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // ── Layer 0: SKETCHER ──────────────────────────────────────────
    [L_SKETCH] = LAYOUT(
        KC_ESC,  KC_NO,   FC_FILE, FC_TRIM,   FC_PROJ,              KC_NO,         FC_FITA,
        KC_NO,   FC_LINE, FC_CIRC, FC_POIN,   FC_HEXA,              FC_LINE,       FC_CONS,
        KC_TAB,  FC_LINE, FC_ARC,  FC_CIRC,   FC_RECT,              FC_POLY,       KC_M,
        KC_DEL,  KC_NO,   KC_NO,   KC_NO,     KC_D,                 KC_NO,         KC_BSPC,
        KC_NO,   KC_NO,   KC_LEFT, KC_RIGHT,  LM(L_CTRL, MOD_LCTL), MO(L_NUMPAD),  MO(L_CONST)
    ),

    // ── Layer 1: CONSTRAINTS ───────────────────────────────────────
    [L_CONST] = LAYOUT(
        KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO, KC_NO,   KC_NO,   FC_SYM,  KC_NO,   KC_NO,   KC_NO,
        KC_NO, FC_COIN, FC_ANGL, FC_HV,   FC_EQUL, FC_TANG, KC_NO,
        KC_NO, FC_PARA, FC_PONL, FC_COIN, FC_PERP, KC_NO,   KC_NO,
        KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS
    ),

    // ── Layer 2: NUMPAD  (ASDFG=5-9, ZXCVB=0-4) ───────────────────
    [L_NUMPAD] = LAYOUT(
        KC_NO, KC_NO,   KC_NO,   KC_BSPC,  KC_SPC,  KC_NO,    KC_NO,
        KC_NO, KC_9,    KC_8,    KC_7,     KC_6,    KC_5,     KC_NO,
        KC_NO, KC_4,    KC_3,    KC_2,     KC_1,    KC_0,     KC_NO,
        KC_NO, KC_LEFT, KC_ASTR, KC_SLSH,  KC_DOT,  KC_RIGHT, KC_NO,
        KC_NO, KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_TRNS,   KC_NO
    ),

    // ── Layer 3: PART DESIGN ───────────────────────────────────────
    [L_PARTDES] = LAYOUT(
        KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO, FC_PAD,  FC_PCKT, FC_REVL, FC_FILT, FC_CHMF, KC_NO,
        KC_NO, FC_THCK, FC_DRFT, C(KC_Z), C(KC_Y), KC_NO,   KC_NO,
        KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
    ),

    // -- layer 4: CTRL
    [L_CTRL] = LAYOUT(
        KC_ESC,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,
        KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,
        KC_NO,   KC_X,   KC_C,   KC_P,   KC_Z,   KC_F2,   KC_NO,
        KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_Y,   KC_DOT,  KC_NO,
        KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO
    ),
};

// ── Macro send logic ─────────────────────────────────────────────────
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true; // fire on keydown only

    switch (keycode) {
        // Draw tools — G-prefix chords
        case FC_LINE: SEND_STRING(SS_TAP(X_G) SS_TAP(X_L)); return false;
        case FC_CIRC: SEND_STRING(SS_TAP(X_G) SS_TAP(X_C)); return false;
        case FC_ARC:  SEND_STRING(SS_TAP(X_G) SS_TAP(X_A)); return false;
        case FC_RECT: SEND_STRING(SS_TAP(X_G) SS_TAP(X_R)); return false;
        case FC_BSPL: SEND_STRING(SS_TAP(X_G) SS_TAP(X_B)); return false;
        case FC_TRIM: SEND_STRING(SS_TAP(X_T) SS_TAP(X_R)); return false;
        case FC_EXTD: SEND_STRING(SS_TAP(X_T) SS_TAP(X_E)); return false;
        case FC_CONS: SEND_STRING(SS_TAP(X_G) SS_TAP(X_N)); return false;
        case FC_FITA: SEND_STRING(SS_TAP(X_V) SS_TAP(X_F)); return false;
        case FC_POLY: SEND_STRING(SS_TAP(X_G) SS_TAP(X_M)); return false;
        case FC_FILE: SEND_STRING(SS_TAP(X_G) SS_TAP(X_F) SS_TAP(X_F)); return false;
        case FC_PROJ: SEND_STRING(SS_TAP(X_G) SS_TAP(X_X)); return false;
        case FC_HEXA: SEND_STRING(SS_TAP(X_G) SS_TAP(X_P) SS_TAP(X_6)); return false;
        case FC_POIN: SEND_STRING(SS_TAP(X_G) SS_TAP(X_Y)); return false;
        // Constraints — single keys
        case FC_COIN: SEND_STRING(SS_TAP(X_C)); return false;
        case FC_HORZ: SEND_STRING(SS_TAP(X_H)); return false;
        case FC_VERT: SEND_STRING(SS_TAP(X_V)); return false;
        case FC_PERP: SEND_STRING(SS_TAP(X_N)); return false;
        case FC_TANG: SEND_STRING(SS_TAP(X_T)); return false;
        case FC_PARA: SEND_STRING(SS_LSFT(SS_TAP(X_P))); return false;
        case FC_PONL: SEND_STRING(SS_LSFT(SS_TAP(X_O))); return false;
        case FC_ANGL: SEND_STRING(SS_TAP(X_K) SS_TAP(X_A)); return false;
        case FC_EQUL: SEND_STRING(SS_TAP(X_E)); return false;
        case FC_SYM: SEND_STRING(SS_TAP(X_S)); return false;
        case FC_HV: SEND_STRING(SS_TAP(X_A)); return false;
        // Part Design
        case FC_PAD:  SEND_STRING(SS_TAP(X_P)); return false;
        case FC_PCKT: SEND_STRING(SS_LSFT(SS_TAP(X_P))); return false;
        case FC_REVL: SEND_STRING(SS_TAP(X_R)); return false;
        case FC_FILT: SEND_STRING(SS_TAP(X_F)); return false;
        case FC_CHMF: SEND_STRING(SS_LSFT(SS_TAP(X_C))); return false;
        case FC_THCK: SEND_STRING(SS_LSFT(SS_TAP(X_T))); return false;
        case FC_DRFT: SEND_STRING(SS_LSFT(SS_TAP(X_F))); return false;
    }
    return true;
}