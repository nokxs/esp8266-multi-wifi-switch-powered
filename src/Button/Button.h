#ifndef Button_h
#define Button_h

#include <Homie.h>

class Button
{
  public:
    Button(uint8_t pin, HomieNode& node)
    : pin(pin)
    , node(node)
    {}
    uint8_t pin;
    HomieNode node;
    unsigned long lastPressed = 0;
    unsigned long lastShortPress = 0;
};

#endif