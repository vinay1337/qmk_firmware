#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _SYMB 1
#define _NAV 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  SYMB,
  NAV,
  ADJUST,
};

// Shortcut to make keymap more readable
#define SYM_L   MO(_SYMB)
#define NAV_L   MO(_NAV)

#define KC_ALAS LALT_T(KC_PAST)
#define KC_CTPL LCTL_T(KC_BSLS)

#define KC_CLFT LCTL_T(KC_LEFT)
#define KC_NAGR LT(_NAV, KC_GRV)
#define KC_NAMI LT(_NAV, KC_MINS)
#define KC_NAES LT(_NAV, KC_ESC) 
#define SYM_ESC LT(_SYMB, KC_ESC) 
#define KC_SYES LT(_SYMB,KC_ESC) 
#define KC_SPSF RSFT_T(KC_SPC)

#define KC_ADEN LT(_ADJUST, KC_END)
#define KC_ADPU LT(_ADJUST, KC_PGUP)


// Tap Dance declarations
enum td_keycodes {
    TD_COLN,
    NAV_ESC,
};
void dance_nav_esc_finished(qk_tap_dance_state_t* state, void* user_data){
   if (state->count == 1){
      layer_on(_NAV);
   }else{
      register_code(KC_ESC);
   }
}
void dance_nav_esc_reset(qk_tap_dance_state_t* state, void* user_data){
   if (state->count == 1){
      layer_off(_NAV);
   }else{
      unregister_code(KC_ESC);
   }
}
qk_tap_dance_action_t tap_dance_actions[] = {
   //  [TD_CTRL] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, MO(_MOVE)),
    [TD_COLN] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
    [NAV_ESC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_nav_esc_finished, dance_nav_esc_reset),
};

#define TD_COLN  TD(TD_COLN)
#define TD_NESC  TD(NAV_ESC)

layer_state_t layer_state_set_user(layer_state_t state){
   return update_tri_layer_state(state, _NAV, _SYMB, _ADJUST);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                         ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                          KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_EQL  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_GRV  ,                        KC_BSLS ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_MINS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                       ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     TD_NESC ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_LBRC ,                        KC_RBRC ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐     ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_ENT  ,KC_DEL  ,      KC_RGUI ,KC_RALT ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤     ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LCTL ,KC_MPLY ,KC_LALT ,KC_LGUI ,     SYM_ESC ,    KC_SPSF ,KC_RCTL ,      KC_BSPC ,KC_SPC ,     NAV_L   ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RIGHT
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘     └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_SYMB] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                         ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                          KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_EXLM ,KC_AT   ,KC_LCBR ,KC_RCBR ,KC_PIPE ,KC_F11  ,                        KC_F12  ,XXXXXXX ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                       ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_HASH ,KC_DLR  ,KC_LBRC ,KC_RBRC ,KC_GRV  ,KC_LPRN ,                        KC_RPRN ,XXXXXXX ,KC_4    ,KC_5    ,KC_6    ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐     ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_PERC ,KC_CIRC ,KC_LPRN ,KC_RPRN ,KC_TILD ,_______ ,_______ ,      _______ ,_______ ,XXXXXXX ,KC_1    ,KC_2    ,KC_3    ,KC_DOT  ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤     ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,      _______ ,KC_UNDS ,    _______ ,     KC_0    ,KC_DOT  ,XXXXXXX ,XXXXXXX 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘     └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                         ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,KC_MS_U ,XXXXXXX ,KC_WH_U ,XXXXXXX ,_______ ,                        _______ ,XXXXXXX ,KC_PGDN ,KC_PGUP ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                       ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_MS_L ,KC_MS_D ,KC_MS_R ,KC_WH_D ,XXXXXXX ,_______ ,                        _______ ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RIGHT,KC_COLN ,KC_DQUO ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐     ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_HOME ,KC_BTN3 ,_______ ,      _______ ,XXXXXXX ,KC_END  ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤     ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     KC_BTN1 ,    KC_BTN2 ,_______ ,      _______ ,_______ ,    XXXXXXX ,     KC_HOME ,KC_PGDN ,KC_PGUP ,KC_END 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘     └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                         ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                          KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,RESET   ,RGB_M_P ,RGB_TOG ,RGB_MOD ,RGB_HUD ,RGB_HUI ,                        RGB_SAD ,RGB_SAI ,RGB_VAD ,RGB_VAI ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                       ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                       XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐     ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,XXXXXXX ,      XXXXXXX ,_______ ,XXXXXXX ,KC_MUTE ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤     ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,XXXXXXX ,      XXXXXXX ,XXXXXXX ,    XXXXXXX ,     KC_MPRV ,KC_VOLD ,KC_VOLU ,KC_MNXT 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘     └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  )
};
