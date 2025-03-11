#include QMK_KEYBOARD_H
#include "gpio.h"

/**
 * @brief Disable the onboard power LED on the Liatris micro controller.
 */
void keyboard_pre_init_user(void) {
    gpio_set_pin_output(24);
    gpio_write_pin_high(24);
}

/**
 * @brief Custom per key tapping terms.

 * @param keycode
 * @param record
 * @return
 */
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    uint16_t offset = 100;
    switch (keycode) {
        case LGUI_T(KC_A):
            return TAPPING_TERM + offset;
        case LALT_T(KC_S):
            return TAPPING_TERM + offset;
        case RGUI_T(KC_SCLN):
            return TAPPING_TERM + offset;
        case RALT_T(KC_L):
            return TAPPING_TERM + offset;
        case RSFT_T(KC_F):
            return TAPPING_TERM - 50;
        case LSFT_T(KC_J):
            return TAPPING_TERM - 50;
        default:
            return TAPPING_TERM;
    }
}

/**
 * @brief Custom per key permissive hold settings.
 *
 * @param keycode
 * @param record
 * @return
 */
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_F):
            return true;
        case LCTL_T(KC_D):
            return true;
        case RSFT_T(KC_J):
            return true;
        case RCTL_T(KC_K):
            return true;
        default:
            return false;
    }
}
