////Library examples for TM1638.
////
////Copyright (C) 2011 Ricardo Batista <rjbatista at gmail dot com>
////
////This program is free software: you can redistribute it and/or modify
////it under the terms of the version 3 GNU General Public License as
////published by the Free Software Foundation.
////
////This program is distributed in the hope that it will be useful,
////but WITHOUT ANY WARRANTY; without even the implied warranty of
////MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
////GNU General Public License for more details.
////
////You should have received a copy of the GNU General Public License
////along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//#define TIMER1_INTERRUPTS_ON     TIMSK1 |=  (1 << OCIE1A);
//#define TIMER1_INTERRUPTS_OFF    TIMSK1 &= ~(1 << OCIE1A);
//
//#include <TM1638.h>
//#include <TM1638QYF.h>
//
//SPISettings qfy(500000, LSBFIRST, SPI_MODE0);
//TM1638QYF module(5, &qfy);
//
//SPISettings led_key(1000000, LSBFIRST, SPI_MODE0);
//TM1638 module2(10, &led_key);
//
//word mode;
//
//unsigned long startTime;
//
//
//void setup() {
//    startTime = millis();
//
//    module.setupDisplay(true, 7);
//    mode = 0;
//
//    // display a hexadecimal number and set the left 4 dots
//    //module.setDisplayToHexNumber(0x1234ABCD, 0xF0);
//    TCNT1 = 0;                         // timer/counter 1 초기화
//    TCCR1A = 0;
//    TCCR1B = 0;
//    OCR1A = 65535;                      // output compare register 1A set
//    TCCR1A |= (0 << WGM11) | (0 << WGM10);
//    TCCR1B |= (0 << WGM13) | (1 << WGM12);  // CTC mode에서 TOP은 OCR1A 사용
//    TCCR1B |= ((1 << CS12) | (0 << CS11) | (1 << CS10));  // clk/1024 prescaler
//    TIMER1_INTERRUPTS_ON
//}
//
//uint16_t maxTCNT;
//uint16_t tempTCNT;
//
//ISR(TIMER1_COMPA_vect) {
//    //TIMER1_INTERRUPTS_OFF
//    //OCR1A = 60000;
//    //module.setDisplayToDecNumber(TCNT1, 0x00);
//}
//
//void update(TM1638QYF* module, word* mode) {
//    word buttons = module->getButtons();
//    unsigned long runningSecs = (millis() - startTime) / 1000;
//
//    // button pressed - change mode
//    if (buttons != 0) {
//        *mode = buttons;
//    }
//
//    switch (*mode) {
//        case sButton::S01:
//            module->setDisplayToDecNumber(runningSecs, 1 << 6);
//            break;
//        case S02:
//            module->setDisplayToDecNumber(runningSecs, 1 << 5, false);
//            break;
//        case S03:
//            module->setDisplayToHexNumber(runningSecs, 1 << 4);
//            break;
//        case S04:
//            module->setDisplayToHexNumber(runningSecs, 1 << 3, false);
//            break;
//        case S05:
//            module->setDisplayToBinNumber(runningSecs, 1 << 2);
//            break;
//        case S06:
//            char s[9];
//            sprintf(s, "Secs %03lu", runningSecs % 999);
//            module->setDisplayToString(s, 1 << 1);
//            break;
//        case S07:
//            if (runningSecs % 2 == 0) {
//                module->setDisplayToString("TM1638QY", 1);
//            }
//            else {
//                module->setDisplayToString(String("LIBRARY "), 1);
//            }
//            break;
//        case S08:
//            module->setDisplayToError();
//            break;
//        case S09:
//            module->setDisplayToDecNumber(*mode, 0);
//            break;
//        case S10:
//            module->setDisplayToString("ABCDE", 1 << (runningSecs % 8));
//            break;
//        default:    // S11 ~ S16
//            module->setDisplayToBinNumber(buttons & 0xF, buttons >> 8);
//    }
//}
//
//void loop() {
//    update(&module, &mode);
//
//    byte keys = module2.getButtons();
//    switch (keys) {
//        case 0b00000001:
//            module2.setDisplayToDecNumber(TCNT1, 0x00);
//            break;
//        case 0b00000010:
//            module2.setDisplayToDecNumber(OCR1A, 0x00);
//            break;
//        case 0b00000100:
//            module2.setDisplayToDecNumber(OCR1B, 0x00);
//            break;
//        default:
//            module2.setDisplayToDecNumber(TCNT1, 0x00);
//            break;
//    }
//}
