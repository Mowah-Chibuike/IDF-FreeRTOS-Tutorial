#include <stdio.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define LED_PIN 2


// Blink the onboard LED
void blink_led(void *pvParameters)
{
	gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT); 	// Set the pinMode of the onboasrd LED as OUTPUT
	gpio_set_level(LED_PIN, 0); 			// Set the pin to be low

	while(1)
	{
		// Toggle the state of the pin after 500ms
		gpio_set_level(LED_PIN, 1);
		vTaskDelay(pdMS_TO_TICKS(500));

		gpio_set_level(LED_PIN, 0);
                vTaskDelay(pdMS_TO_TICKS(500));
	}
}

// User entry point: Registers and create the task to blink the onboard LED
void app_main(void)
{
	// Register and Create the task
	xTaskCreate(blink_led, "blink_led", 2048, NULL, 5, NULL);
}
