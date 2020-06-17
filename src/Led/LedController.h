#include <Homie.h>

#ifndef LedController_h
#define LedController_h

class LedController
{
public:
  void setup();
  void loop();

private:
  std::map<uint8_t, String> ledStatesMap = {};
  unsigned long shortTickMs = 0;
  unsigned long longTickMs = 0;
  unsigned long trippleTickMs = 0;
  bool doShortTrippleTick = true;
  int trippleTickCount = 0;
  void setupLED(const char *id, const char *name, uint8_t pin);
  bool ledHandler(const String &value, const String &property, uint8_t pin);
  void togglePin(uint8_t pin);
  bool shouldDoShortPulse();
  bool shouldDoLongPulse();
  bool shouldDoTripplePulse();
};

#endif