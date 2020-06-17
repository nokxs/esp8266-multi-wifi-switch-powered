#include <Led/LedController.h>
#include <Led/LedStates.h>
#include <Homie.h>
#include <Pins.h>
#include <Debugger.h>

typedef std::function<bool(const HomieRange &range, const String &value)> PropertyInputHandler;

HomieNode ledsNode("led-notification", "LEDs", "notification");

void LedController::setup()
{
  setupLED("led-1", "LED 1", PIN_LED1);
  setupLED("led-2", "LED 2", PIN_LED2);
  setupLED("led-3", "LED 3", PIN_LED3);
}

void LedController::setupLED(const char *id, const char *name, uint8_t pin)
{
  ledsNode
      .advertise(id)
      .setName(name)
      .setDatatype("enum")
      .setFormat(LED_FORMAT)
      .setRetained(false)
      .settable([this, id, pin](HomieRange range, String value) { return ledHandler(value, id, pin); });
}

bool LedController::ledHandler(const String &value, const String &property, uint8_t pin)
{
  Debugger::info("Handler: Set pin '" + String(pin) + "' (" + property + ") to '" + value + "'");

  if (value == LED_OFF || value == LED_ON || value == LED_SHORT_PULSE || value == LED_LONG_PULSE || value == LED_TRIPPLE_PULSE)
  {
    digitalWrite(pin, LOW); // Ensure the pin has a defined state

    ledStatesMap.erase(pin);
    ledStatesMap.insert({pin, value});

    ledsNode.setProperty(property).send(value);
  }
  else
  {
    Debugger::info(value + " is a not regognized value");
    return false;
  }

  return true;
}

void LedController::loop()
{
  bool doShortPulse = shouldDoShortPulse();
  bool doLongPulse = shouldDoLongPulse();
  bool doTripplePulse = shouldDoTripplePulse();

  for (auto const &ledState : ledStatesMap)
  {
    int8_t pin = ledState.first;
    String value = ledState.second;

    if (value == LED_OFF)
    {
      digitalWrite(pin, LOW);
      ledStatesMap.erase(pin);
    }
    else if (value == LED_ON)
    {
      digitalWrite(pin, HIGH);
      ledStatesMap.erase(pin);
    }
    else if (value == LED_SHORT_PULSE)
    {
      if (doShortPulse)
      {
        togglePin(pin);
      }
    }
    else if (value == LED_LONG_PULSE)
    {
      if (doLongPulse)
      {
        togglePin(pin);
      }
    }
    else if (value == LED_TRIPPLE_PULSE)
    {
      if (doTripplePulse)
      {
        togglePin(pin);
      }
    }
  }
}

void LedController::togglePin(uint8_t pin)
{
  digitalWrite(pin, !digitalRead(pin));
}

bool LedController::shouldDoShortPulse()
{
  if (shortTickMs + 100 <= millis())
  {
    shortTickMs = millis();
    return true;
  }

  return false;
}

bool LedController::shouldDoLongPulse()
{
  if (longTickMs + 500 <= millis())
  {
    longTickMs = millis();
    return true;
  }

  return false;
}

bool LedController::shouldDoTripplePulse()
{
  if (doShortTrippleTick)
  {
    if (trippleTickMs + 100 <= millis())
    {
      trippleTickMs = millis();

      if (trippleTickCount > 6)
      {
        doShortTrippleTick = false;
        trippleTickCount = 0;
      }
      else
      {
        trippleTickCount++;
      }

      return true;
    }
  }
  else
  {
    if (trippleTickMs + 800 <= millis())
    {
      trippleTickMs = millis();
      doShortTrippleTick = true;
    }
  }

  return false;
}