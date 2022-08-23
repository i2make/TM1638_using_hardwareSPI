/*

#ifndef S01
#define S01     0b0000000000000001
#define S02     0b0000000000000010
#define S03     0b0000000000000100
#define S04     0b0000000000001000
#define S05     0b0000000000010000
#define S06     0b0000000000100000
#define S07     0b0000000001000000
#define S08     0b0000000010000000
#define S09     0b0000000100000000
#define S10     0b0000001000000000
#define S11     0b0000010000000000
#define S12     0b0000100000000000
#define S13     0b0001000000000000
#define S14     0b0010000000000000
#define S15     0b0100000000000000
#define S16     0b1000000000000000
#endif

#define TIMER1_INTERRUPTS_ON     TIMSK1 |=  (1 << OCIE1A);
#define TIMER1_INTERRUPTS_OFF    TIMSK1 &= ~(1 << OCIE1A);

#include <TM1638.h>
#include <TM1638QYF.h>

TM1638QYF module(11, 13, 5);

word mode;

unsigned long startTime;



void setup() {
    startTime = millis();

    module.setupDisplay(true, 7);
    mode = 0;

    // display a hexadecimal number and set the left 4 dots
    //module.setDisplayToHexNumber(0x1234ABCD, 0xF0);
    TCNT1 = 0;                         // timer/counter 1 초기화
    TCCR1A = 0;
    TCCR1B = 0;
    OCR1A = 65535;                      // output compare register 1A set
    TCCR1A |= (0 << WGM11) | (0 << WGM10);
    TCCR1B |= (0 << WGM13) | (1 << WGM12);  // CTC mode에서 TOP은 OCR1A 사용
    TCCR1B |= ((1 << CS12) | (0 << CS11) | (1 << CS10));  // clk/1024 prescaler
    TIMER1_INTERRUPTS_ON
}

uint16_t maxTCNT;
uint16_t tempTCNT;

ISR(TIMER1_COMPA_vect) {
        //TIMER1_INTERRUPTS_OFF
        //OCR1A = 60000;
        //module.setDisplayToDecNumber(TCNT1, 0x00);
}

void update(TM1638QYF* module, word* mode) {
    word buttons = module->getButtons();
    unsigned long runningSecs = (millis() - startTime) / 1000;

    // button pressed - change mode
    if (buttons != 0) {
        *mode = buttons;
    }

    switch (*mode) {
        case S01:
            module->setDisplayToDecNumber(runningSecs, 1 << 6);
            break;
        case S02:
            module->setDisplayToDecNumber(runningSecs, 1 << 5, false);
            break;
        case S03:
            module->setDisplayToHexNumber(runningSecs, 1 << 4);
            break;
        case S04:
            module->setDisplayToHexNumber(runningSecs, 1 << 3, false);
            break;
        case S05:
            module->setDisplayToBinNumber(runningSecs, 1 << 2);
            break;
        case S06:
            char s[9];
            sprintf(s, "Secs %03lu", runningSecs % 999);
            module->setDisplayToString(s, 1 << 1);
            break;
        case S07:
            if (runningSecs % 2 == 0) {
                module->setDisplayToString("TM1638QY", 1);
            }
            else {
                module->setDisplayToString(String("LIBRARY "), 1);
            }
            break;
        case S08:
            module->setDisplayToError();
            break;
        case S09:
            module->setDisplayToDecNumber(*mode, 0);
            break;
        case S10:
            module->setDisplayToString("ABCDE", 1 << (runningSecs % 8));
            break;
        default:    // S11 ~ S16
            module->setDisplayToBinNumber(buttons & 0xF, buttons >> 8);
    }
}

void loop() {
    update(&module, &mode);
}
*/
