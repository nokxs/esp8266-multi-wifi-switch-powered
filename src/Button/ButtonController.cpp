#include <Pins.h>
#include <Debugger.h>
#include <Button/ButtonController.h>
#include <Button/Button.h>

// Homie properties
#define PROPERTY_SHORT_PRESS "shortPress"
#define PROPERTY_LONG_PRESS "longPress"
#define PROPERTY_DOUBLE_PRESS "doubblePress"

#define STRING_TRUE "true"

HomieNode button1("button-1", "Button 1", "switch");
HomieNode button2("button-2", "Button 2", "switch");
HomieNode button3("button-3", "Button 3", "switch");
HomieNode button4("button-4", "Button 4", "switch");

Button buttons[4] = {
    Button(PIN_BUTTON1_INPUT, button1),
    Button(PIN_BUTTON2_INPUT, button2),
    Button(PIN_BUTTON3_INPUT, button3),
    Button(PIN_BUTTON4_INPUT, button4)};

void ButtonController::setup()
{
    for (auto &&button : buttons)
    {
        setupButton(button.node);
    }
}

void ButtonController::loop()
{
    for (auto &&button : buttons)
    {
        handleButton(button);
    }
}

void ButtonController::setupButton(HomieNode& node)
{
    node.advertise(PROPERTY_SHORT_PRESS).setName("Short press").setDatatype("boolean").setRetained(false);
    node.advertise(PROPERTY_LONG_PRESS).setName("Long press").setDatatype("boolean").setRetained(false);
    node.advertise(PROPERTY_DOUBLE_PRESS).setName("Double press").setDatatype("boolean").setRetained(false);
}

void ButtonController::handleButton(Button& button)
{
    int buttonValue = digitalRead(button.pin);

    if (buttonValue == HIGH)
    {
        if (button.lastPressed == 0)
        {
            button.lastPressed = millis();
        }
    }
    else if (button.lastPressed > 0 && button.lastPressed + 10 < millis())
    {
        // long press
        if (button.lastPressed + 250 <= millis())
        {
            Debugger::info("Long press: " + String(button.pin));
            button.node.setProperty(PROPERTY_LONG_PRESS).send(STRING_TRUE);
        }
        // double press
        else if (button.lastPressed + 10 <= millis())
        {
            if (button.lastShortPress + 250 >= millis()) 
            {
                Debugger::info("Double press: " + String(button.pin));
                button.node.setProperty(PROPERTY_DOUBLE_PRESS).send(STRING_TRUE);
                button.lastShortPress = 0;
            }
            else
            {
                button.lastShortPress = millis();
            }
        }

        button.lastPressed = 0;
    } 
    // short press
    else if (button.lastShortPress != 0 && button.lastShortPress + 250 <= millis()) {
            Debugger::info("Short press: " + String(button.pin));
            button.node.setProperty(PROPERTY_SHORT_PRESS).send(STRING_TRUE);
            button.lastShortPress = 0;
    }
}
