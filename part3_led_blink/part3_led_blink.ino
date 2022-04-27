
static const int led_pin = LED_BUILTIN;

void BlinkLED(void * parameter){
    while(1){
        digitalWrite(led_pin,HIGH);
        vTaskDelay(500/portTICK_PERIOD_MS); 
        digitalWrite(led_pin,LOW);
        vTaskDelay(500/portTICK_PERIOD_MS);
      }
  }

  void setup(){
     
      pinMode(led_pin,OUTPUT);
      xTaskCreatePinnedToCore(
          BlinkLED, 
          "Blink LED", 
          1024, 
          NULL, 
          1,  
          NULL, 
          1);  
    }

    void loop(){

    }

