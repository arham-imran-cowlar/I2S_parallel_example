/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "i2s_parallel.h"

/*   I2S i2s_parallel interface configure part  */

#define  CLK  GPIO_NUM_38

#define  D0  GPIO_NUM_2
#define  D1  GPIO_NUM_1
#define  D2  GPIO_NUM_8
#define  D3  GPIO_NUM_7
#define  D4  GPIO_NUM_6
#define  D5  GPIO_NUM_5
#define  D6  GPIO_NUM_4
#define  D7  GPIO_NUM_3

#define  D8   GPIO_NUM_9
#define  D9   GPIO_NUM_10
#define  D10  GPIO_NUM_11
#define  D11  GPIO_NUM_12
#define  D12  GPIO_NUM_13
#define  D13  GPIO_NUM_14
#define  D14  GPIO_NUM_15
#define  D15  GPIO_NUM_16

#define  D16   GPIO_NUM_17
#define  D17   GPIO_NUM_18
#define  D18  GPIO_NUM_19
#define  D19  GPIO_NUM_20
#define  D20  GPIO_NUM_21
#define  D21  GPIO_NUM_26
#define  D22  GPIO_NUM_27
#define  D23  GPIO_NUM_28

i2s_parallel_pin_config_t i2s_parallel_bus = {
    .bit_width = 8,
    .pin_clk = CLK,
    .data = {D8, D9, D10, D11, D12, D13, D14, D15}, // D8, D9, D10, D11, D12, D13, D14, D15, D16, D17, D18, D19, D20, D21, D22, D23},
};

typedef struct {
    uint8_t bits_7_0;
    // uint8_t bits_15_8;
    // uint8_t bits_23_16;
} parallel_data_t;

parallel_data_t data[4096];

void app_main(void)
{
    printf("Hello world!\n");

    for (uint32_t x = 0; x < 4096; x++) {
        // data[x].bits_23_16 =  x;
        // data[x].bits_15_8 =   x;
        data[x].bits_7_0 =    x;
    }

    i2s_parallel_init(&i2s_parallel_bus, 4);// clk_fre = 40MHz / clk_div

    while (1) {
        i2s_parallel_write_data((uint8_t *)data, sizeof(parallel_data_t) * 4096);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
