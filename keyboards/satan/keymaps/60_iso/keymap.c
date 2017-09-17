#include "quantum.h"

#define BASE 0
#define ALT1 1

#define XXX KC_NO
#define ___ KC_TRNS

#define LAYOUT_ISO_60( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,      \
	k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, \
	k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c,      \
	k40, k41, k42,           k45,                     k4a, k4b, k4c, k4d  \
) \
{ \
	{k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d}, \
	{k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX}, \
	{k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d}, \
	{k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, XXX, k3c}, \
	{k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, XXX, k4a, k4b, k4c, k4d}  \
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_ISO_60(
    KC_NUBS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,
    LT(ALT1, KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_BSLS, KC_ENT,
    KC_LSFT, KC_GRV, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, SFT_T(KC_UP),
    KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_RGUI, KC_LEFT, KC_DOWN, KC_RIGHT
  ),
  [ALT1] = LAYOUT_ISO_60(
    ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, RESET,
    ___, ___, ___, ___, ___, ___, KC_MRWD, KC_MPLY, KC_MFFD, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, KC_MUTE, KC_VOLD, KC_VOLU, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___,           ___,                     ___, ___, ___, ___
  )
};

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
