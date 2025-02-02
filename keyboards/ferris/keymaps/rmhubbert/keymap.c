#include <stdint.h>
#include "action.h"
#include "keycodes.h"
#include QMK_KEYBOARD_H
#include "keymap.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
