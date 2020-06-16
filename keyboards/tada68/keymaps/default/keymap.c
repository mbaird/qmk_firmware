#include QMK_KEYBOARD_H

#define BASE 0
#define ALT1 1

#define XXX KC_NO
#define ___ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[BASE] = LAYOUT_iso(
    KC_NUBS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, XXX, \
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, XXX, \
    LT(ALT1,KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT, KC_PGUP, \
    KC_LSFT, KC_GRV, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_PGDN, \
    KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_RGUI, KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
  ),
	[ALT1] = LAYOUT_iso(
    ___, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, ___, RESET, \
    ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, \
    ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, KC_MPLY, \
    ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, KC_VOLU, KC_MUTE, \
    ___, ___, ___, ___, ___, ___, ___, KC_MRWD, KC_VOLD, KC_MFFD
  )
};

/* void matrix_init_user(void); */
/* void matrix_scan_user(void); */
static bool control_disabled = false;
static bool delete_pressed = false;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  if(keycode == KC_BSPC) {
    if (record->event.pressed) {
      if(keyboard_report->mods & MOD_BIT(KC_LCTL)) {
        delete_pressed = true;
        control_disabled = true;
        unregister_code(KC_LCTL);
        register_code(KC_DEL);
        return false;
      }
    } else if(delete_pressed) {
      delete_pressed = false;
      unregister_code(KC_DEL);

      if(control_disabled) {
        control_disabled = false;
        register_code(KC_LCTL);
      }
      return false;
    }
  } else if(keycode == KC_LCTL && !record->event.pressed && delete_pressed) {
    delete_pressed = false;
    control_disabled = false;
    unregister_code(KC_DEL);
    register_code(KC_BSPC);
    return false;
  }
  return true;
};
