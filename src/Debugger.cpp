#include <Debugger.h>
#include <Homie.h>
#include <Arduino.h>

static HomieNode debuggerNode("debugger", "debugger", "debug");

void Debugger::setup()
{
    debuggerNode
        .advertise("debugger")
        .setName("Debugger")
        .setDatatype("string")
        .setRetained(false);
}

void Debugger::info(String message)
{
    if (Serial)
    {
        Serial.println("INFO: " + message);
    }

    debuggerNode.setProperty("debugger").send("INFO: " + message);
}