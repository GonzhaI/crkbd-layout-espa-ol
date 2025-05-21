#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _NAV,
    _NUM,
    _FN
};

enum custom_keycodes {
    E_NTIL = SAFE_RANGE, // ñ
    E_IQUE               // ¿
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case E_NTIL:
                // Alt + 164 = ñ
                register_code(KC_LALT);
                tap_code(KC_KP_1);
                tap_code(KC_KP_6);
                tap_code(KC_KP_4);
                unregister_code(KC_LALT);
                return false;

            case E_IQUE:
                // Alt + 168 = ¿
                register_code(KC_LALT);
                tap_code(KC_KP_1);
                tap_code(KC_KP_6);
                tap_code(KC_KP_8);
                unregister_code(KC_LALT);
                return false;
        }
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Base Layer: Español QWERTY */
    [_BASE] = LAYOUT_split_3x6_3(
        KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    E_NTIL,  KC_ALGR,
        KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_QUES, KC_CAPS,
                                   KC_LGUI, MO(_NAV), KC_SPC,        KC_ENT, MO(_NUM), KC_LALT
    ),

   /* _BASE
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |BackSP|
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |LCTRL |   A  |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |   Ñ  |AltGr |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |LShift|   Z  |   X  |   C  |   V  |   B  |--------.   .-------|   N  |   M  |  ,<  |  .>  |   ?  |CapLok|
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *                          | LGUI | _NAV | /Space  /       \Enter \  | _NUM | LAlt |
    *                          |      |      |/       /         \      \ |      |      |
    *                          `---------------------'           '------''-------------'
    */

    /* NAV Layer: Flechas a la izquierda, símbolos a la derecha */
    [_NAV] = LAYOUT_split_3x6_3(
        KC_ESC,  KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_CIRC,        KC_LPRN, KC_RPRN, KC_SLSH, KC_BSLS, KC_NUHS, KC_DEL,
        KC_LCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_AMPR,        KC_LCBR, KC_RCBR, KC_MINS, KC_PLUS, KC_SCLN, KC_QUOT,
        KC_LSFT, KC_EXLM, KC_AT,   KC_NUHS, KC_DLR,  KC_PERC,        KC_LBRC, KC_RBRC, KC_EQL,  KC_ASTR, E_IQUE,  KC_PIPE,
                                   _______, _______, _______,        _______, MO(_FN), _______
    ),

    /* _NAV
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * | ESC  | Home |  Up  |  End | PgUp |   ^  |                    |   (  |   )  |   /  |   \  |   _  | DEL  |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |LCTRL | Left | Down |Right |PgDown|   &  |                    |   {  |   }  |  -_  |   +  |  ;:  |  '"  | 
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |LShift|   !  |   @  |  #~  |  $   |   %  |--------.    .------|   [  |   ]  |   =  |   *  |   ¿  |   |  |
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *                          | LGUI | _NAV | /Space  /       \Enter \  | _NUM | LAlt |
    *                          |      |      |/       /         \      \ |      |      |
    *                          `---------------------'           '------''-------------'
    */

    /* NUM Layer: Controles multimedia izquierda, pad numérico derecha */
    [_NUM] = LAYOUT_split_3x6_3(
        KC_NO,   KC_F24,  KC_NO,   KC_MPLY, KC_MPRV, KC_MNXT,        KC_NO,   KC_7,    KC_8,    KC_9, KC_PPLS,   KC_DEL,
        KC_NO,   KC_NO,   KC_NO,   KC_MUTE, KC_VOLD, KC_VOLU,        KC_NO,   KC_4,    KC_5,    KC_6, KC_PMNS,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,          KC_0,    KC_1,    KC_2,    KC_3, KC_PENT,   KC_NO,
                                   _______, MO(_FN), _______,        _______, _______, _______
    ),

    /* _NUM
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |      |  F24 |      | Pause|Previo| Next |                    |      |   7  |   8  |   9  |      |  DEL |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |      |      |      | Mute |VolDow|VolUp |                    |      |   4  |   5  |   6  |      |      |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |      |      |      |      |      |      |--------.   .-------|   0  |   1  |   2  |   3  |      |      |
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *                          | LGUI | _NAV | /Space  /       \Enter \  | _NUM | LAlt |
    *                          |      |      |/       /         \      \ |      |      |
    *                          `---------------------'           '------''-------------'
    */

    /* FN Layer: Funciones F1-F12 */
    [_FN] = LAYOUT_split_3x6_3(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,          KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______,        _______, _______, _______
    )

    /* ADJUST
    * ,-----------------------------------------.                    ,-----------------------------------------.
    * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
    * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
    * |      |      |      |      |      |      |-------.    .-------|      |      |      |      |      |      |
    * `-----------------------------------------/       /     \      \-----------------------------------------'
    *                          | LGUI | _NAV | /Space  /       \Enter \  | _NUM | LAlt |
    *                          |      |      |/       /         \      \ |      |      |
    *                          `---------------------'           '------''-------------'
    */
};
