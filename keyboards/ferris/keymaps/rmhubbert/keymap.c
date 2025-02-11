/*#include <stdint.h>*/
/*#include "action.h"*/
/*#include "config.h"*/
/*#include "keycodes.h"*/
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
        case TD(TD_LEFT_HOME_THUMB):
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

/*TAP DANCE*/

// Keep track of key presses for Modifier
typedef struct {
    bool is_press_action;
    int  state;
} tap;

// Key Tap enumerator
enum {
    SINGLE_TAP  = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP  = 3,
    DOUBLE_HOLD = 4,
};

// Calculate the correct tap dance action, based on the current state.
int cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->pressed) {
            return SINGLE_HOLD;
        } else {
            return SINGLE_TAP;
        }
    } else if (state->count == 2) {
        if (state->pressed) {
            return DOUBLE_HOLD;
        } else {
            return DOUBLE_TAP;
        }
    } else
        return 8;
}

// Left home thumb tap dance
// SINGLE_TAP = One shot layer 2 (symbol layer).
// SINGLE_HOLD = Activate layer 1 (movement layer).
// DOUBLE_TAP = Toggle layer 3 (number layer).
void left_home_thumb_finished(tap_dance_state_t *state, void *user_data);
void left_home_thumb_reset(tap_dance_state_t *state, void *user_data);

static tap left_home_thumb_tap_state = {.is_press_action = true, .state = 0};

void left_home_thumb_finished(tap_dance_state_t *state, void *user_data) {
    left_home_thumb_tap_state.state = cur_dance(state);
    switch (left_home_thumb_tap_state.state) {
        case SINGLE_TAP:
            set_oneshot_layer(2, ONESHOT_START);
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
        case SINGLE_HOLD:
            layer_on(1);
            break;
        case DOUBLE_TAP:
            layer_move(3);
            break;
        case DOUBLE_HOLD:
            break;
    }
}

void left_home_thumb_reset(tap_dance_state_t *state, void *user_data) {
    switch (left_home_thumb_tap_state.state) {
        case SINGLE_TAP:
            break;
        case SINGLE_HOLD:
            layer_off(1);
            break;
        case DOUBLE_TAP:
            break;
        case DOUBLE_HOLD:
            break;
    }
    left_home_thumb_tap_state.state = 0;
}

// Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_LEFT_HOME_THUMB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, left_home_thumb_finished, left_home_thumb_reset),
};
