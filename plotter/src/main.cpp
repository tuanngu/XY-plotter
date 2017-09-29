#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

#include "user_vcom.h"
#include "Laser.h"
#include "Servo.h"
#include "StepperMotor.h"

#include "FreeRTOS.h"
#include "task.h"

void setupHardware();

/* Task Declaration */
void vReceiveTask(void *vParameters);
void vExecuteTask(void *vParameters);

/* Motor */

int main(void) {

    setupHardware();

    xTaskCreate(vReceiveTask, "Receive Task", configMINIMAL_STACK_SIZE,
                NULL, (tskIDLE_PRIORITY + 1UL), (TaskHandle_t *) NULL);

    xTaskCreate(vExecuteTask, "Execute Task", configMINIMAL_STACK_SIZE,
                NULL, (tskIDLE_PRIORITY + 1UL), (TaskHandle_t *) NULL);

    xTaskCreate(cdc_task, "CDC Task", configMINIMAL_STACK_SIZE * 2, NULL,
                (tskIDLE_PRIORITY + 1UL), (TaskHandle_t *) NULL);


    vTaskStartScheduler();

    while (1)
        ;

    return 0;
}

void setupHardware() {
    SystemCoreClockUpdate();
    Board_Init();

    Board_LED_Set(0, false);
}

/***** Task Definition *****/

void vReceiveTask(void *vParameters) {

    while (1) {

    }
}

void vExecuteTask(void *vParameters) {

    while (1) {

    }
}

/* the following is required if runtime statistics are to be collected */
extern "C" {

/* X axis motor */
void SCT2_IRQHandler(void) {

}

/* Y axis motor */
void SCT3_IRQHandler(void) {

}

void vConfigureTimerForRunTimeStats(void) {
    Chip_SCT_Init(LPC_SCTSMALL1);
    LPC_SCTSMALL1->CONFIG = SCT_CONFIG_32BIT_COUNTER;
    LPC_SCTSMALL1->CTRL_U = SCT_CTRL_PRE_L(255) | SCT_CTRL_CLRCTR_L; // set prescaler to 256 (255 + 1), and start timer
}

}
/* end runtime statistics collection */
