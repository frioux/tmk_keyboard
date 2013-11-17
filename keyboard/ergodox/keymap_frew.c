#include <util/delay.h>
#include "action_layer.h"
#include "action_util.h"
#include "bootloader.h"
#include "keymap_common.h"


const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Default Layer
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |  esc   |   1  |   2  |   3  |   4  |   5  |   6  |           |      |   7  |   8  |   9  |   0  |   -  |   =    |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |   ~    |   Q  |   W  |   E  |   R  |   T  |   \  |           |   [  |   Y  |   U  |   I  |   O  |   P  |   ]    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |  Tab   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  | Quote  |
     * |--------+------+------+------+------+------| ~Fn1 |           | ~Fn1 |------+------+------+------+------+--------|
     * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | Rshift |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | Pause| '->' | '::' | '=>' |      |                                       |      |      |      |      |  Win |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        | LCtrl| LAlt |       | RAlt | RCtrl|
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      | Home |       | PgUp |      |      |
     *                                 | BkSp |  Win |------|       |------| Enter| Space|
     *                                 |      |      |      |       | PgDn |      |      |
     *                                 `--------------------'       `--------------------'
     */

    KEYMAP(  // layout: layer 0: default
        // left hand
        ESC, 1,   2,   3,   4,   5,     6,
        GRV, Q,   W,   E,   R,   T,  BSLS,
        TAB, A,   S,   D,   F,   G,
        LSFT,Z,   X,   C,   V,   B,   FN1,
        PAUS, NO, NO,  NO,   NO,
                                     LCTL, LALT,
                                           HOME,
                                 BSPC,LGUI,  NO,
        // right hand
              NO, 7,   8,   9,   0,   MINS, EQL,
            LBRC, Y,   U,   I,   O,   P,   RBRC,
                  H,   J,   K,   L,   SCLN,QUOT,
             FN1, N,   M,   COMM,DOT, SLSH,RSFT,
                         NO,NO, NO,     NO,  NO,
        RALT,RCTL,
        PGUP,
        PGDN, ENT, SPC
    ),

    KEYMAP(  // layout: layer 1: F-keys instead of numbers
        // left hand
        FN7,   F1,  F2,  F3,  F4,  F5,  F6,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             TRNS,  F7,  F8,  F9, F10, F11, F12,
             TRNS,FN8,TRNS,TRNS,TRNS,FN9,RBRC,
                  LEFT,DOWN,  UP,RGHT,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),

};

/* id for user defined functions */
enum function_id {
    TEENSY_KEY,
};

enum macro_id {
    COPY,
    PASTE,
};

/*
 * Fn action definition
 */
const action_t PROGMEM fn_actions[] = {
   [0] = ACTION_DEFAULT_LAYER_SET(0),                    // switch to Layer0
   [1] = ACTION_LAYER_MOMENTARY(1),                      // push Layer1
   [7] = ACTION_FUNCTION(TEENSY_KEY),                    // Teensy key

   [8] = ACTION_MACRO(COPY),                            // Macro: CTRL+C
   [9] = ACTION_MACRO(PASTE),                           // Macro: CTRL+V
};

void action_function(keyrecord_t *event, uint8_t id, uint8_t opt)
{
    print("action_function called\n");
    print("id  = "); phex(id); print("\n");
    print("opt = "); phex(opt); print("\n");
    if (id == TEENSY_KEY) {
        clear_keyboard();
        print("\n\nJump to bootloader... ");
        _delay_ms(250);
        bootloader_jump(); // should not return
        print("not supported.\n");
    }
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    keyevent_t event = record->event;
    tap_t tap = record->tap;

    switch (id) {
        case COPY:
            return (event.pressed ?
                    MACRO( I(0), D(LCTL), T(C), U(LCTL), END ) :
                    MACRO_NONE );
        case PASTE:
            return (event.pressed ?
                    MACRO( I(0), D(LCTL), T(V), U(LCTL), END ) :
                    MACRO_NONE );
    }
    return MACRO_NONE;
}
