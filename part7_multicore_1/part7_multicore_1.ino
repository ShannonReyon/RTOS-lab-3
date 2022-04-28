static const BaseType_t pro_cpu = 0;
static const BaseType_t app_cpu = 1;

static const TickType_t time_hog = 200;  // Time (ms) hogging the CPU

// Hogs the processor. Accurate to about 1 second.
static void hog_delay(uint32_t ms) {
  for (uint32_t i = 0; i < ms; i++) {
    for (uint32_t j = 0; j < 40000; j++) {
      asm("nop");
    }
  }
}

void print_taskB(void *parameters) {
  
  TickType_t timestamp;
  char str[30];

  while (1) {

    sprintf(str, "I am Task B I am Running on CORE_ %i \n", xPortGetCoreID());
    Serial.print(str);

    hog_delay(time_hog);
  }
}

// Task H (high priority)
void print_taskA(void *parameters) {
  
  TickType_t timestamp;
  char str[30];

  while (1) {

    sprintf(str, "I am Task A I am Running on CORE_ %i \n", xPortGetCoreID());
    Serial.print(str);
    
    // Hog the processor for a while doing nothing (this is a bad idea)
    hog_delay(time_hog);
  }
}

void setup() {

  Serial.begin(115200);

  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("---FreeRTOS Priority Inheritance Demo---");
  
  xTaskCreatePinnedToCore(print_taskA,
                          "Task A",
                          3000,
                          NULL,
                          1,
                          NULL,
                          pro_cpu);

  xTaskCreatePinnedToCore(print_taskB,
                          "Task B",
                          3000,
                          NULL,
                          2,
                          NULL,
                          app_cpu);

  // Delete "setup and loop" task
  vTaskDelete(NULL);
}

void loop() {
  // Execution should never get here
}

