#include "Particle.h"

int relay[5] = {D4,D5,D6,D7,D8};

//our events are called when IFTTT applets are triggered
void offHandler(const char *event, const char *data)
{
        for (int i = 0; i < 5; i++) // Setup GPIO
        {
                digitalWrite(relay[i], LOW); // set LOW
        }
}
void onHandler(const char *event, const char *data)
{
        for (int i = 0; i < 5; i++) // Setup GPIO
        {
                digitalWrite(relay[i], HIGH); // set LOW
        }
}

int setRelay(String args)
{
        bool relayState;
        int commaLoc = args.indexOf(",");

        String relayString = args.substring(0,commaLoc);
        String stateString = args.substring(commaLoc+1);

        Particle.publish("log", relayString + " " + stateString);

        if (stateString.equals("on")) {
                relayState = LOW;
        }
        else {
                relayState = HIGH;
        }

        int relayNumber = relayString.toInt();

        pinMode(relay[relayNumber-1], OUTPUT); // set as output
        digitalWrite(relay[relayNumber-1], relayState);

        return 0;
}

// setup() is run only once, it's where we set up GPIO and initialise peripherals
void setup() {

        for (int i = 0; i < 5; i++) // Setup GPIO
        {
                pinMode(relay[i], OUTPUT); // set as output
                digitalWrite(relay[i], HIGH); // set HIGH
        }

        // Subscribe to events published by IFTTT using Particle.subscribe
        Particle.subscribe("LOWERPATH-OFFxxx", offHandler); // turning off .. Want to vary this as Relay 01, 02 etc
        Particle.subscribe("LOWERPATH-ONxxx", onHandler); // turning on...I Want to add more commands to switch differing relays.

        Particle.function("setRelay", setRelay);
}

// loop() runs continuously, it's our infinite loop.
void loop() {

// empty because handlers and cloud function manage the relays

}
