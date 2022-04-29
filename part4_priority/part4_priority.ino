#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif
// Some string to print
const char msg[] = "Task 1 is running";
// Task handles
static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;
//*****************************************************************************
// Tasks
// Task: print to Serial Terminal with lower priority
void startTask1(void *parameter) {
  // Count number of characters in string
  int msg_len = strlen(msg);
  // Print string to Terminal
  while (1) {
      Serial.println();
    for (int i = 0; i < msg_len; i++) {
      Serial.print(msg[i]);
  }
  Serial.println();
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
// Task: print to Serial Terminal with higher priority
void startTask2(void *parameter) {
  while (1) {
    Serial.print('*');
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void setup(){
  // Configure serial and wait a second
  Serial.begin(9600); 
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  // Start task 1
  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
            startTask1,      // Function to be called
            "Task 1",   // Name of task
            1024,           // Stack size (bytes in ESP32, words in FreeRTOS)
            NULL,           // Parameter to pass
            2,              // Task priority
            NULL,           // Task handle
            app_cpu);       // Run on one core for demo purposes (ESP32 only)

  // Start task 2
  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
            startTask2,      // Function to be called
            "Task 2",   // Name of task
            1024,           // Stack size (bytes in ESP32, words in FreeRTOS)
            NULL,           // Parameter to pass
            1,              // Task priority
            NULL,           // Task handle
            app_cpu);       // Run on one core for demo purposes (ESP32 only)
  // Delete "setup and loop" task
    vTaskDelete(NULL);

}

void loop() {
  // Execution should never get here
}

