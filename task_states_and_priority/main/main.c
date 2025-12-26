#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Low-priority task → Prints every 1s
void low_priority(void *pvParameters)
{
	while (1)
	{
		vTaskDelay(pdMS_TO_TICKS(1000));
		printf("Low priority says that she's alive..\n");
	}
}

// Medium-priority task → Prints every 500ms
void medium_priority(void *pvParameters)
{
	while (1)
	{
		vTaskDelay(pdMS_TO_TICKS(500));
		printf("Medium priority says hello...\n");
	}
}

// High-priority task → Runs at startup, changes its own priority to lowest
// after 5 iterations
void high_priority(void *pvParameters)
{
	int counter = 1;

	while (1)
	{
		printf("High priority task is the boss... Count: %d\n", counter++);
		if (counter == 5)
		{
			vTaskPrioritySet(NULL, 2);
		}
	}
}


void app_main(void)
{
	xTaskCreate(low_priority, "Low Priority", 2048, NULL, 3, NULL);
	xTaskCreate(medium_priority, "Medium Priority", 2048, NULL, 4, NULL);
	xTaskCreate(high_priority, "High Priority", 2048, NULL, 5, NULL);
}
