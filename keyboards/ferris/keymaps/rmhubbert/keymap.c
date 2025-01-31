#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*base layer*/
    [0] = LAYOUT_split_3x5_2(
        KC_Q, KC_W, KC_E, KC_R, KC_T,                                           KC_Y, KC_U, KC_I, KC_O, KC_P,
        LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), KC_G,           KC_H, RSFT_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RGUI_T(KC_SCLN),
        KC_Z, KC_X, KC_C, KC_V, KC_B,                                           KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
        LT(3,KC_ESC), LT(1,KC_BSPC),                                            LT(2,KC_SPC), LT(4,KC_TAB)
    ),

    /*movement layer*/
    [1] = LAYOUT_split_3x5_2(
        KC_NO, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO,                                KC_NO, KC_ESC, KC_ENT, KC_TAB, KC_BSPC,
        LALT_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), KC_NO,          KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_QUOT,
        KC_NO, KC_NO, KC_CAPS, CW_TOGG, KC_NO,                                  KC_NO, KC_NO, KC_NO, KC_NO, KC_BSLS,
        KC_TRNS, KC_TRNS,                                                       KC_TRNS, KC_TRNS
    ),

    /*symbol layer*/
    [2] = LAYOUT_split_3x5_2(
        KC_EXLM, KC_DQUO, KC_HASH, KC_DLR, KC_PERC,                             KC_CIRC, KC_AMPR, KC_ASTR, KC_P0, KC_NO,
        KC_MINS, KC_LCBR, KC_LBRC, KC_LPRN, KC_EQL,                             RALT(KC_3), RSFT_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RGUI_T(KC_SCLN),
        KC_NUBS, KC_RCBR, KC_RBRC, KC_RPRN, KC_NO,                              KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_TRNS,                                                       KC_TRNS, KC_TRNS
    ),

    /*number layer*/
    [3] = LAYOUT_split_3x5_2(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                      KC_PSLS, KC_7, KC_8, KC_9, KC_PPLS,
        LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT(KC_F), KC_NO,            KC_PAST, KC_4, KC_5, KC_6, KC_PEQL,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                      KC_0, KC_1, KC_2, KC_3, KC_PMNS,
        KC_TRNS, KC_TRNS,                                                       KC_TRNS, KC_TRNS
    ),

    /*mouse and functions layer*/
    [4] = LAYOUT_split_3x5_2(
        MS_WHLU, MS_BTN1, MS_UP, MS_BTN2, KC_NO,                                KC_F9, KC_F10, KC_F11, KC_F12, KC_NO,
        MS_WHLD, MS_LEFT, MS_DOWN, MS_RGHT, KC_NO,                              KC_F5, KC_F6, KC_F7, KC_F8, KC_NO,
        KC_WSCH, KC_WBAK, KC_WFWD, KC_WREF, KC_NO,                              KC_F1, KC_F2, KC_F3, KC_F4, QK_BOOT,
        KC_TRNS, KC_TRNS,                                                       KC_TRNS, KC_TRNS
    )
};
// clang-format on



#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C

