/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "muse.h"


enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MOVE,
  _DVORAK,
  _COLEMAK,
  _PLOVER,
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  BACKLIT,
  DVORAK,
  COLEMAK,
  PLOVER,
  EXT_PLV
};

typedef enum {
    SINGLE_TAP,
    SINGLE_HOLD,
    DOUBLE_SINGLE_TAP
} td_state_t;

static td_state_t td_state;

// Tap Dance definitions
uint8_t cur_dance(qk_tap_dance_state_t *state){
  if (state->count == 1) {
      if (state->interrupted || !state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
  }

  if (state->count == 2) return DOUBLE_SINGLE_TAP;
  else return 3; // Any number higher than the maximum state value you return above
}
// void td_ctrl_each(qk_tap_dance_state_t *state, void *user_data) {

// }
void td_ctrl_finished(qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      // register_code16(KC_LPRN);
      register_mods(MOD_BIT(KC_RCTL));
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_RCTL)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
      break;
    case DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
      register_mods(MOD_BIT(KC_RCTL) | MOD_BIT(KC_RSFT));
      // tap_code16(KC_LPRN);
      // register_code16(KC_LPRN);
      break;
  }
}
void td_ctrl_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      // unregister_code16(KC_LPRN);
      unregister_mods(MOD_BIT(KC_RCTL));
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_RCTL)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
      break;
    case DOUBLE_SINGLE_TAP:
      unregister_mods(MOD_BIT(KC_RCTL) | MOD_BIT(KC_RSFT));
        // unregister_code16(KC_LPRN);
      break;
    }
}

// Tap Dance declarations
enum td_keycodes {
    TD_CTRL,
    TD_COLN,
    TD_QUOT,
    SFTENTR,
    NAV_ESC,
};
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_CTRL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_ctrl_finished, td_ctrl_reset),
    // [TD_CTRL] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, MO(_MOVE)),
    [TD_COLN] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
    [TD_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO),
    [SFTENTR] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_ENT),
    [NAV_ESC] = ACTION_TAP_DANCE_DUAL_ROLE(KC_ESC, _MOVE)
};

#define LOWER    MO(_LOWER)
#define RAISE    MO(_RAISE)
#define NAVIG    MO(_MOVE)
#define ESC_NAV  LT(_MOVE, KC_ESC)
#define ENTRSFT  TD(SFTENTR) //RSFT_T(KC_ENT)
#define TD_CTRL  TD(TD_CTRL)
#define TD_COLN  TD(TD_COLN)
#define TD_QUOT  TD(TD_QUOT)
#define ONESHFT  OSM(MOD_LSFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB , KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    ESC_NAV, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    TD_COLN, TD_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, ENTRSFT,
    KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   TD_CTRL, KC_RGUI, KC_RALT, NAVIG
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_GRV , KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
    KC_TILD, _______, _______, _______, KC_LBRC, KC_LCBR, KC_RCBR, KC_RBRC, KC_MINS, KC_EQL , KC_PLUS, KC_PIPE,
    _______, _______, _______, _______, KC_LPRN, _______, _______, KC_RPRN, KC_LABK, KC_RABK, KC_BSLS, _______,
    _______, _______, _______, _______, _______, KC_UNDS, KC_UNDS, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_GRV,  KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9  , KC_0   , KC_DEL ,
    KC_ESC,  KC_APP , KC_PSCR, _______, _______, _______, _______, KC_4   , KC_5   , KC_6  , KC_MINS, KC_EQL ,
    _______, KC_MPRV, KC_MUTE, KC_MNXT, KC_MPLY, _______, _______, KC_1   , KC_2   , KC_3  , KC_PLUS, KC_ENT ,
    _______, _______, _______, _______, _______, KC_UNDS, KC_UNDS, _______, KC_0   , KC_DOT, _______, _______
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|TermOf|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    KC_F12 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
    _______, _______, _______, DEBUG  , _______, RGB_TOG, RGB_VAI, KC_VOLD, KC_VOLU, _______, _______, _______,
    _______, _______, _______, _______, _______, RGB_HUI, RGB_SAI, _______, _______, _______, RESET  , _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),


[_MOVE] = LAYOUT_planck_grid(
    _______, _______, KC_MS_U, _______, KC_WH_U, _______, _______, KC_PGDN, KC_PGUP, KC_MINS, KC_EQL , KC_DEL ,
    _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_COLN, KC_DQUO,
    _______, _______, _______, KC_WH_L, KC_WH_R, KC_HOME, KC_END , _______, _______, _______, _______, KC_ENT ,
    _______, _______, KC_BTN3, KC_BTN2, KC_BTN1, _______, _______, _______, _______, _______, _______, _______
)

};





#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          writePinLow(E6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          writePinHigh(E6);
        #endif
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_song); }
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
                layer_off(_ADJUST);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}

// LEADER_EXTERNS();

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
// LEADER_DICTIONARY() {
//     leading = false;
//     leader_end();

//     SEQ_ONE_KEY(KC_L) {
//       // Anything you can do in a macro.
//       register_code(KC_LGUI);
//       register_code(KC_L);
//       unregister_code(KC_L);
//       unregister_code(KC_LGUI);
//     }
//     SEQ_TWO_KEYS(KC_C, KC_C) {
//       tap_code(KC_CAPS);
//     }
//     SEQ_TWO_KEYS(KC_P, KC_P) {
//       tap_code(KC_PSCR);
//     }
//     SEQ_FIVE_KEYS(KC_R, KC_E, KC_S, KC_E, KC_T) {
//       reset_keyboard();
//     }
//   }
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
