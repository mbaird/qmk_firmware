#include "quantum.h"

#define BASE 0
#define ALT1 1

#define XXX KC_NO
#define ___ KC_TRNS

/* TADA68 ISO layout
   * ,----------------------------------------------------------------.
   * | 00 |01| 02| 03| 04| 05| 06| 07| 08| 09| 0a| 0b| 0c| 0d    | 0e |
   * |----------------------------------------------------------------|
   * | 10  | 11| 12| 13| 14| 15| 16| 17| 18| 19| 1a| 1b| 1c|  1d | 1e |
   * |----------------------------------------------------------------|
   * | 20    | 21| 22| 23| 24| 25| 26| 27| 28| 29| 2a| 2b| 2d    | 2e |
   * |----------------------------------------------------------------|
   * | 30     | 32| 33| 34| 35| 36| 37| 38| 39| 3a| 3b|    3c| 3d| 3e |
   * |----------------------------------------------------------------|
   * | 40 | 41 | 42 |        45             | 49| 4a|  4b| 4c| 4d| 4e |
   * `----------------------------------------------------------------'
 */

#define LAYOUT_ISO_TADA( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,      k1e, \
	k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, \
	k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, \
	k40, k41, k42,           k45,                k49, k4a, k4b, k4c, k4d, k4e  \
) \
{ \
	{k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e}, \
	{k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, XXX, k1e}, \
	{k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e}, \
	{k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e}, \
	{k40, k41, k42, XXX, XXX, k45, XXX, XXX, XXX, k49, k4a, k4b, k4c, k4d, k4e}  \
}

void matrix_init_user(void);
void matrix_scan_user(void);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_ISO_TADA(
    KC_NUBS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, XXX, \
    KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, XXX, \
    LT(ALT1, KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, XXX, KC_ENT, KC_PGUP, \
    KC_LSFT, KC_GRV, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_PGDN, \
    KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_RGUI, KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
  ),
  [ALT1] = LAYOUT_ISO_TADA(
    ___, KC_F1, KC_F2, ___, ___, ___, ___, ___, ___, ___, ___, KC_F11, ___, ___, RESET, \
    ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, \
    ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, KC_MPLY, \
    ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, KC_VOLU, KC_MUTE, \
    ___, ___, ___, ___, ___, ___, ___, KC_MRWD, KC_VOLD, KC_MFFD
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
