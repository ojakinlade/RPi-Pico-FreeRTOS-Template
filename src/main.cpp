#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

TaskHandle_t blinkTaskHandle = NULL;

void BlinkTask(void* pvParameters)
{  
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    for(;;)  
    {
        gpio_put(PICO_DEFAULT_LED_PIN, true);
        vTaskDelay(pdMS_TO_TICKS(1000));
        gpio_put(PICO_DEFAULT_LED_PIN, false);
        vTaskDelay(pdMS_TO_TICKS(1000));
    } 
}

int main(void)
{
    stdio_init_all();

    xTaskCreate(BlinkTask, "BlinkTask", 256, NULL, 1, &blinkTaskHandle);
    vTaskStartScheduler();

    while(true)
    {

    }
}