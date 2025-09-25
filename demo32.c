#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LCD.h"
#include "Keypad.h"
#include "LED.h"

char password[4];
char input[4];
int input_index = 0;
bool password_generated = false;

void generate_password() {
    for (int i = 0; i < 4; i++) {
        password[i] = '1' + rand() % 6; // 產生 '1'~'6'
        display_seven_segment(i, password[i]); // 顯示在七段
    }
    password_generated = true;
}

void clear_input() {
    input_index = 0;
    clear_LCD();
}

void check_password() {
    if (input_index == 0) {
        printS(0, 0, "NULL");
        return;
    }

    if (memcmp(password, input, 4) == 0) {
        printS(0, 0, "PASS");
        led_marquee();
    } else {
        printS(0, 0, "ERROR");
        led_flash_all();
    }
}

void keypad_handler(char key) {
    if (key >= '1' && key <= '6') {
        if (input_index < 4) {
            input[input_index++] = key;
        }
    } else if (key == 'R') {
        generate_password();
    } else if (key == 'C') {
        clear_input();
    } else if (key == 'O') {
        check_password();
    }
}

int main() {
    init_LCD();
    init_keypad();
    init_LED();
    srand(TIMER2->TDR); // 使用 Timer 作為亂數種子

    while (1) {
        char key = get_keypad_input();
        keypad_handler(key);
    }
}
