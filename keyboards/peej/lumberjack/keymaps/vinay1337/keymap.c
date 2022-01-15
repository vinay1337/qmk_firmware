/* Copyright 2020 Paul James
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

enum layers {
  _QWERTY = 0,
  _FUNCTION,
  _MOVE,
  _ADJUST,
  _GAME
};

enum custom_keycodes {
    GITFETCH = SAFE_RANGE,
    GITINIT,
};

#define ENTRSFT RSFT_T(KC_ENT)
#define ESC_MOV LT(_MOVE, KC_ESC)
#define RET_MOV LT(_MOVE, KC_ENT)
#define BSLSCTL LCTL_T(KC_BSLS)
#define SPCSFT  RSFT_T(KC_SPC)
#define SPCTL   LCTL_T(KC_SPC)
#define FN_SPC  LT(_FUNCTION, KC_SPC)
#define FN      MO(_FUNCTION)
#define GIT     LT(_ADJUST, KC_GRV)
#define GAME    TG(_GAME)
#define KOT     KEY_OVERRIDE_TOGGLE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------. ,-----------------------------------------.
 * |   `  |  1   |  2   |  3   |  4   |  5   | |  6   |  7   |  8   |  9   |  0   | BkSp |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Tab  |  Q   |  W   |  E   |  R   |  T   | |  Y   |  U   |  I   |  O   |  P   | Del  |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Esc  |  A   |  S   |  D   |  F   |  G   | |  H   |  J   |  K   |  L   |  ;   |  '   |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Shft |  Z   |  X   |  C   |  V   |  B   | |  N   |  M   |  ,   |  .   |  /   | Entr |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Ctrl |  Fn  | Alt  | Cmd  |  Fn  | Spac | | Spac |  Fn  | Left | Down |  Up  | Rght |
 * `-----------------------------------------' `-----------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_5x12(
    GIT   ,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
    ESC_MOV, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL, FN,      KC_LALT, KC_LGUI, KC_LCTL, SPCSFT,  KC_SPC,  FN     , KC_RCTL, KC_RGUI, KC_RALT, RET_MOV
),

/* Function
* ,------------------------------------------. ,-----------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  | |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  | |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  | |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 | |  F12 |ISO # |ISO / |      |      |      |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |      |      |      |      |      | |      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------' `-----------------------------------------'
 */
[_FUNCTION] = LAYOUT_ortho_5x12(
    KC_ESC , KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL ,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL , KC_PIPE,
    KC_TILD, _______, C(KC_S), KC_LCBR, KC_LBRC, KC_LPRN, KC_RPRN, KC_RBRC, KC_RCBR, _______, KC_COLN, KC_DQUO, 
    _______, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), _______, _______, _______, KC_LABK, KC_RABK, KC_BSLS, _______,
    _______, _______, _______, _______, _______, _______, KC_UNDS, KC_MUTE, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

[_MOVE] = LAYOUT_ortho_5x12(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL ,
    _______, _______, KC_MS_U, _______, KC_WH_U, _______, _______, KC_PGDN, KC_PGUP, _______, _______, KC_EQL ,
    _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_COLN, KC_DQUO,
    _______, _______, _______, _______, _______, KC_HOME, KC_END , _______, _______, _______, KC_BSLS, KC_ENT ,
    _______, _______, KC_BTN3, KC_BTN2, KC_BTN1, _______, _______, _______, _______, _______, _______, _______
),

[_ADJUST] = LAYOUT_ortho_5x12(
    _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_F12 ,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,GITFETCH, GITINIT, _______, _______, _______, _______, _______, GAME   , KOT    , _______, RESET
),

[_GAME] = LAYOUT_ortho_5x12(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, KC_LCTL, KC_SPC , KC_SPC , _______, _______, _______, _______, _______, _______
)
};


// KEY OVERRIDES
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPACE, KC_DELETE);
const key_override_t underscore_space_override = ko_make_basic(MOD_BIT(KC_RSFT), KC_SPC, KC_UNDS);
// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &delete_key_override,
    &underscore_space_override,
    NULL // Null terminate the array of overrides!
};

// COMBOS
const uint16_t PROGMEM combo1[] = {KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM combo2[] = {KC_Y, KC_U, COMBO_END};
const uint16_t PROGMEM combo3[] = {KC_P, KC_MINS, COMBO_END};
const uint16_t PROGMEM combo4[] = {KC_O, KC_P, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo1, KC_LBRC),
    COMBO(combo2, KC_RBRC), // keycodes with modifiers are possible too!
    COMBO(combo3, KC_EQL),
    COMBO(combo4, KC_PLUS),
};

// MACROS
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case GITFETCH:
        if (record->event.pressed) {
            // when keycode GITFETCH is pressed
            SEND_STRING("git fetch; git status\n");
        } else {
            // when keycode GITFETCH is released
        }
        break;
    case GITINIT:
        if (record->event.pressed){
            SEND_STRING("git config --global user.name 'Vinay Janardhanam'\n");
            SEND_STRING("git config --global user.email vjanard");
        } else {

        }
        break;
    }
    return true;
};