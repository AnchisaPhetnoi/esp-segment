#include <stdio.h>
#include "LED.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

LED seg_a(16);
LED seg_b(17);
LED seg_c(5);
LED seg_d(18);
LED seg_e(19);
LED seg_f(21);
LED seg_g(22);
LED digit_1(0);  // สำหรับหลักสิบ
LED digit_2(4);  // สำหรับหลักหน่วย

void DisplayDigit(int digit, int number) {
    if (digit == 1) {
        digit_1.ON();
        digit_2.OFF();
    } else if (digit == 2) {
        digit_1.OFF();
        digit_2.ON();
    }

    seg_a.OFF();
    seg_b.OFF();
    seg_c.OFF();
    seg_d.OFF();
    seg_e.OFF();
    seg_f.OFF();
    seg_g.OFF();

    switch (number) {
        case 0: seg_a.ON(); seg_b.ON(); seg_c.ON(); seg_d.ON(); seg_e.ON(); seg_f.ON(); break;
        case 1: seg_b.ON(); seg_c.ON(); break;
        case 2: seg_a.ON(); seg_b.ON(); seg_d.ON(); seg_e.ON(); seg_g.ON(); break;
        case 3: seg_a.ON(); seg_b.ON(); seg_c.ON(); seg_d.ON(); seg_g.ON(); break;
        case 4: seg_b.ON(); seg_c.ON(); seg_f.ON(); seg_g.ON(); break;
        case 5: seg_a.ON(); seg_c.ON(); seg_d.ON(); seg_f.ON(); seg_g.ON(); break;
        case 6: seg_a.ON(); seg_c.ON(); seg_d.ON(); seg_e.ON(); seg_f.ON(); seg_g.ON(); break;
        case 7: seg_a.ON(); seg_b.ON(); seg_c.ON(); break;
        case 8: seg_a.ON(); seg_b.ON(); seg_c.ON(); seg_d.ON(); seg_e.ON(); seg_f.ON(); seg_g.ON(); break;
        case 9: seg_a.ON(); seg_b.ON(); seg_c.ON(); seg_d.ON(); seg_f.ON(); seg_g.ON(); break;
    }
}

void DisplayNumber(int tens, int units) {
    for (int i = 0; i < 200; i++) {  // ทำซ้ำเพื่อแสดงผลได้นานขึ้น
        DisplayDigit(1, tens);
        vTaskDelay(10 / portTICK_PERIOD_MS);  // เพิ่มดีเลย์เพื่อให้ตัวเลขติดนานขึ้น

        DisplayDigit(2, units);
        vTaskDelay(10 / portTICK_PERIOD_MS);

        digit_1.OFF();
        digit_2.OFF();
    }
}

void DisplaySequence() {
    int sequence[][2] = {{6, 5}, {2, 0}, {3, 0}, {2, 8}, {0, 9}};
    int numPairs = sizeof(sequence) / sizeof(sequence[0]);

    for (int i = 0; i < numPairs; i++) {
        DisplayNumber(sequence[i][0], sequence[i][1]);
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // ดีเลย์ระหว่างคู่ตัวเลขแต่ละคู่
    }
}

extern "C" void app_main(void) {
    while (1) {
        DisplaySequence();
        vTaskDelay(2000 / portTICK_PERIOD_MS);  // รอระหว่างรอบการแสดงลำดับทั้งหมด
    }
}
