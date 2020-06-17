#ifndef ButtonController_h
#define ButtonController_h

#include <Homie.h>
#include <Button/Button.h>

class ButtonController
{
  public:
    void setup();
    void loop();
  private:
    void setupButton(HomieNode& node);
    void handleButton(Button& button);
};

#endif