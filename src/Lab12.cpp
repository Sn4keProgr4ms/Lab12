/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/admin/Desktop/Remys_Labs/Lab12/src/Lab12.ino"
#include <MQTT.h>
#include <oled-wing-adafruit.h>

void setup();
void loop();
void resetDisplay();
#line 4 "/Users/admin/Desktop/Remys_Labs/Lab12/src/Lab12.ino"
#define LED D7

void callback(char *topic, byte *payload, unsigned int length);

MQTT client("lab.thewcl.com", 1883, callback);

SYSTEM_THREAD(ENABLED);

OledWingAdafruit display;

void setup()
{

  display.setup();

  pinMode(LED, OUTPUT);

  client.subscribe("remyLab12");
}
void loop()
{

  if (client.isConnected())
  {
    client.loop();
  }
  else
  {
    client.connect(System.deviceID());
    client.subscribe("remyLab12");
  }
  display.loop();

  // publishes information if oled buttons are pressed
  if (display.pressedA())
  {
    client.publish("remyLab12", "A");
  }
  if (display.pressedB())
  {
    client.publish("remyLab12", "B");
  }
  if (display.pressedC())
  {
    client.publish("remyLab12", "C");
  }
}
void callback(char *topic, byte *payload, unsigned int length)
{
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;

  if (String(p).equals("1"))
  {
    digitalWrite(LED, HIGH);
  }
  else if (String(p).equals("0"))
  {
    digitalWrite(LED, LOW);
  }
  else
  {
    resetDisplay();
    display.println(p);
    display.display();
  }
}

void resetDisplay()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
}