#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

#define LED_PIN 	2
#define BLINK_TIMING 	500

TaskHandle_t blinkTaskHandler = NULL;

// blinkTask – blinks an LED every 500 ms, self-deletes after 10 blinks
void blinkTask(void *pvParameters)
{
	int counter = 0;

	gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
	gpio_set_level(LED_PIN, 0);

	while (1)
	{
		gpio_set_level(LED_PIN, 1);
		vTaskDelay(pdMS_TO_TICKS(BLINK_TIMING));

		gpio_set_level(LED_PIN, 0);
		vTaskDelay(pdMS_TO_TICKS(BLINK_TIMING));

		counter++;
		if (counter >= 10)
		{
			printf("Blink Task self destructing... \n");
			vTaskDelete(NULL);
		}
	}
}

// Manager Task – deletes the Blink Task after 5 seconds if still running
void managerTask(void *pvParameters)
{
	printf("Manager Task running... \n");
	vTaskDelay(pdMS_TO_TICKS(5000));

	if (blinkTaskHandler != NULL)
	{
		printf("Manager Task obliterating Blink Task... \n");
		vTaskDelete(blinkTaskHandler);
		gpio_set_level(LED_PIN, 0);
	}
	vTaskDelete(NULL);
}

void app_main(void)
{
	BaseType_t err;

	err = xTaskCreate(blinkTask, "Blink Task", 2048, NULL, 5, &blinkTaskHandler);
	if (err != pdPASS)
	{
		printf("Something went wrong...\n");
		return;
	}

	err = xTaskCreate(managerTask, "Manager Task", 2048, NULL, 4, NULL);
	if (err != pdPASS)
	{
		printf("Something went wrong... \n");
		return;
	}
}
