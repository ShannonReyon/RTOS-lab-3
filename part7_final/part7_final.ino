#include<WiFi.h>
static const BaseType_t pro_cpu = 0;
static const BaseType_t app_cpu = 1;

static const TickType_t time_hog = 200;  // Time (ms) hogging the CPU

const char* ssid = "EN20401726";
const char* password = "12345678";

// Hogs the processor. Accurate to about 1 second.
static void hog_delay(uint32_t ms) {
  for (uint32_t i = 0; i < ms; i++) {
    for (uint32_t j = 0; j < 40000; j++) {
      asm("nop");
    }
  }
}

void Connect_to_WIFI(void *parameters) {
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  Serial.print("Connecting to wiFi");

  while(WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.print("\nconnected to the wiFi network");
  Serial.print("IP Address");
  Serial.println(WiFi.localIP());
}

// Task H (high priority)
void BlinkLED(void * parameter){
    while(1){
      Serial.print("blinking");

        digitalWrite(13,HIGH);
        vTaskDelay(500/portTICK_PERIOD_MS); 
        digitalWrite(13,LOW);
        vTaskDelay(500/portTICK_PERIOD_MS);
      }
  }

void setup() {

  Serial.begin(115200);

  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("---FreeRTOS Priority Inheritance Demo---");
  
  xTaskCreatePinnedToCore(Connect_to_WIFI,
                          "WIFI",
                          3000,
                          NULL,
                          1,
                          NULL,
                          pro_cpu);

  xTaskCreatePinnedToCore(BlinkLED,
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
