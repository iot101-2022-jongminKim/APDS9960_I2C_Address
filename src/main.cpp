// Disconnect Interrupt Pin

#include <Arduino.h>
#include <SSD1306.h>
#include <Wire.h>
#include <SparkFun_APDS9960.h>

SSD1306 display(0x3c, 4, 5, GEOMETRY_128_32);
SparkFun_APDS9960 apds = SparkFun_APDS9960();
int isr_flag = 0;

void handleGesture()
{
    display.clear();
    if (apds.isGestureAvailable())
    {
        switch (apds.readGesture())
        {
        case DIR_UP:
            Serial.println("UP");
            display.drawString(12, 12, "UP");
            display.display();
            break;

        case DIR_DOWN:
            Serial.println("DOWN");
            display.drawString(12, 12, "DOWN");
            display.display();
            break;

        case DIR_LEFT:
            Serial.println("LEFT");
            display.drawString(12, 12, "LEFT");
            display.display();
            break;

        case DIR_RIGHT:
            Serial.println("RIGHT");
            display.drawString(12, 12, "RIGHT");
            display.display();
            break;

        default:
            Serial.println("NONE");
            display.drawString(12, 12, "NONE");
            display.display();
        }
    }
    delay(250);
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Starting APDS-9960 Gesture");

    if (apds.init())
    {
        Serial.println("APDS-9960 initialization complete");
    }
    else
    {
        Serial.println("Something went wrong during APDS-9960 init!");
    }

    if (apds.enableGestureSensor(false))
    { // Start APDS-9960 gesture sensor engine
        Serial.println("Gesture sensor is now running");
    }
    else
    {
        Serial.println("Something went wrong during gesture sensor init!");
    }

    display.init();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_10);
    display.drawString(12, 12, "Hello World");
    display.display();

    for (int addr = 0; addr < 128; addr++)
    {
        Serial.println();
        Serial.print(addr);
        Serial.print(" wire address: ");
        Wire.beginTransmission(addr);
        int error = Wire.endTransmission();

        if (error == 0)
        {
            if (addr != 60)
            {
                Serial.print(" APDS9960 I2C address: ");
                Serial.print(addr); // address: 0x3C = 0011 1100 -> 60
            }
            else
            {
                Serial.print(" SSD1306 display address: ");
                Serial.print(addr); // address: 0x3C = 0011 1100 -> 60
            }
        }
    }
    Serial.println();
}

void loop()
{
    // char buff[10];
    // sprintf(buff, "%5d", lux);
    handleGesture();
}
