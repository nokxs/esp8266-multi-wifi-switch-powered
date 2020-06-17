#include <Debugger.h>
#include <Homie.h>
#include <Pins.h>
#include <Led/LedStates.h>
#include <Led/LedController.h>
#include <Button/ButtonController.h>

LedController ledController;
ButtonController buttonController;

void loopHandler()
{
  ledController.loop();
  buttonController.loop();
}

void setup()
{
  // Serial.begin(115200);
  pinMode(D9, FUNCTION_3);

  pinMode(PIN_BUTTON1_INPUT, INPUT);
  pinMode(PIN_BUTTON2_INPUT, INPUT);
  pinMode(PIN_BUTTON3_INPUT, INPUT);
  pinMode(PIN_BUTTON4_INPUT, INPUT);

  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);

  Homie_setFirmware("home-control-center", "1.0.0");
  Homie_setBrand("Home Control Center");
  
  Homie.disableLedFeedback();
  Homie.setLoopFunction(loopHandler);

  Debugger::setup();

  ledController.setup();
  buttonController.setup();

  Homie.setup();
  Debugger::info("Setup done");
}

void loop()
{
  Homie.loop();
}