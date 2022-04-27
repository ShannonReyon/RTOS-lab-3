//Configure output pins
static const int led_pin = LED_BUILTIN;

//TASK OF BLINK
void BlinkLED(void * parameter){
    while(1){
        digitalWrite(led_pin,HIGH);
        vTaskDelay(500/portTICK_PERIOD_MS); //portTick_PERIOD_MS = 1ms
        digitalWrite(led_pin,LOW);
        vTaskDelay(500/portTICK_PERIOD_MS);
      }
  }

  void setup(){
      //configuration pin
      pinMode(led_pin,OUTPUT);

      //Task to run forever
      xTaskCreatePinnedToCore(
          BlinkLED, //fn to be called
          "Blink LED", //Name of task
          1024, //stack size(bytes in esp32,words in FreeRTOS,,,,,,min b = 768
          NULL, //parameter to pass to function
          1,  //Task priority (0 to configMAX_PRIORITIES -1)
          NULL, //Task handle
          1);   //run on one core
    }

    void loop(){

    }

