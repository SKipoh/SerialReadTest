#include <Arduino.h>

// 8-bit Byte value to store a counter value
// just used to check the code loops correctly
byte count;
// Setting up integer value to read the pot value too
int potVal;
// Defining pin PA7 to be named "potValPin"
#define potValPin PA7

// Defining the built in LED pin
#define ledPin PB12
// Mapping the switch to a GPIO pin
#define switch2 PA4


void setup () {

    pinMode(ledPin, OUTPUT);
    pinMode(switch2, INPUT);
    Serial.begin(9600);

}


int debouncer (bool swReading, bool lastSwReading, bool swledState) {

    // Has the state of the button changed?
    if (swReading == !lastSwReading) {
        // If YES, then we update the last state to be the current state
        lastSwReading = swReading;

        // Switch goes HIGH -> LOW
        if (swReading == LOW) {
            // Updating the LED state
            swledState = !swledState;
            // Returning the new state
            return swledState;
        }

    }
    return swledState;

}

void loop (bool swReading, bool lastSwReading, bool swLedState) {

    // Reading the current value of a switch
    swReading = digitalRead(switch2);

    // Sending that reading off to be debounced and latched
    swLedState = debouncer(swReading, lastSwReading, swLedState);
    // Writing the returned value to the onboard LED
    digitalWrite(switch2, swLedState);


    Serial.print("Button Reading: ");
    Serial.print(swReading);
    Serial.println();

    Serial.print("Current Count: ");
    Serial.print(count);
    Serial.println();
    Serial.print("Current Reading: ");
    Serial.print(swReading);
    Serial.println();
    Serial.print("Last Reading: ");
    Serial.print(lastSwReading);
    Serial.println();
    Serial.print("LED State: ");
    Serial.print(swLedState);
    Serial.println();


    // Reading in the value from the pot
    potVal = analogRead(potValPin);

    // caluclating voltage from the value we read in
    float potVolts = (float(potVal)/4096) * 3.3;

    //digitalWrite(ledPin, HIGH);
    //delay(500);

    Serial.print("Potentiometer Value: ");
    Serial.print(potVal);
    Serial.println();
    Serial.print("Potentiometer Voltage: ");
    Serial.print(potVolts);
    Serial.println();

    Serial.print("Count: ");
    Serial.print(count);
    Serial.println();

    digitalWrite(ledPin, LOW);
    delay(500);

    count++;
}