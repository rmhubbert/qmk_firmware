#include <stdint.h>
#include "action.h"
#include "config.h"
#include "keycodes.h"
#include QMK_KEYBOARD_H
#include "keymap.h"
#include "features/custom_shift_keys.h"

/**
 * @brief Define any custom shift keys.
 */
const custom_shift_key_t custom_shift_keys[] = {
    {KC_LBRC, KC_RBRC}, // Shift [ is ]
    {KC_LCBR, KC_RCBR}, // Shift { is }
    {KC_LPRN, KC_RPRN}, // Shift ( is )
};

uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

/**
 * @brief Custom keycode processing.
 *
 * @param keycode
 * @param record
 * @return
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_custom_shift_keys(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case LGUI_T(KC_A):
            // disable accidental mod when rolling s & a
            if (!disable_modifier_user(record, KC_LALT, KC_S, KC_A)) return false;
            // disable accidental mod when rolling d & a
            if (!disable_modifier_user(record, KC_LCTL, KC_D, KC_A)) return false;
            // disable accidental mod when rolling f & a
            if (!disable_modifier_user(record, KC_LSFT, KC_F, KC_A)) return false;
        case LALT_T(KC_S):
            // disable accidental mod when rolling a & s
            if (!disable_modifier_user(record, KC_LGUI, KC_A, KC_S)) return false;
            // disable accidental mod when rolling d & s
            if (!disable_modifier_user(record, KC_LCTL, KC_D, KC_S)) return false;
            // disable accidental mod when rolling f & s
            if (!disable_modifier_user(record, KC_LGUI, KC_F, KC_S)) return false;
        case LCTL_T(KC_D):
            // disable accidental mod when rolling a & d
            if (!disable_modifier_user(record, KC_LGUI, KC_A, KC_D)) return false;
        case LSFT_T(KC_F):
            // disable accidental mod when rolling a & f
            return disable_modifier_user(record, KC_LGUI, KC_A, KC_F);
        case RCTL_T(KC_K):
            // disable accidental mod when rolling l & k
            if (!disable_modifier_user(record, KC_RALT, KC_L, KC_K)) return false;
    }
    return true;
};

/**
 * @brief Convenience function to handle custom home row mod customisation.
 *
 * @param record
 * @param keycode
 * @param first_tap
 * @param second_tap
 * @return
 */
bool disable_modifier_user(keyrecord_t *record, uint16_t keycode, uint16_t first_tap, uint16_t second_tap) {
    if (record->event.pressed && record->tap.count > 0) {
        if (get_mods() & MOD_BIT(keycode)) {
            unregister_mods(MOD_BIT(keycode));
            tap_code(first_tap);
            tap_code(second_tap);
            add_mods(MOD_BIT(keycode));
            return false;
        }
    }
    return true;
};

/**
 * @brief Custom per key tapping terms.

 * @param keycode
 * @param record
 * @return
 */
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    uint16_t offset = 50;
    switch (keycode) {
        case LGUI_T(KC_A):
            return TAPPING_TERM + offset;
        case LALT_T(KC_S):
            return TAPPING_TERM + offset;
        case RGUI_T(KC_SCLN):
            return TAPPING_TERM + offset;
        case RALT_T(KC_L):
            return TAPPING_TERM + offset;
        default:
            return TAPPING_TERM;
    }
}

/**
 * @brief Custom per key quick tap terms. This is needed to allow multi tap toggles when you have
 * set QUICK_TAP_TERM to 0.
 *
 * @param keycode
 * @param record
 * @return
 */
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TT(3):
            return TAPPING_TERM;
        default:
            return QUICK_TAP_TERM;
    }
}
