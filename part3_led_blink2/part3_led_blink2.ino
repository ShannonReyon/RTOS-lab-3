static const int rate_1 = 500;  
static const int rate_2 = 300;  

static const int led_pin = LED_BUILTIN;

// Task 1
void LED_1(void *parameter) {
  while(1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(rate_1 / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(rate_1 / portTICK_PERIOD_MS);
  }
}

// Task 2
void LED_2(void *parameter) {
  while(1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(rate_2 / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(rate_2 / portTICK_PERIOD_MS);
  }
}

void setup() {

  pinMode(led_pin, OUTPUT);

  xTaskCreatePinnedToCore(  
              LED_1,  
              "LED 1",   
              1024,         
              NULL,        
              1,           
              NULL,         
              1);     

  xTaskCreatePinnedToCore(  
              LED_2,  
              "LED 2",   
              1024,         
              NULL,        
              1,           
              NULL,         
              1);     
}

void loop() {

}

