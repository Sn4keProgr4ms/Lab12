#include <MQTT.h>
#include <oled-wing-adafruit.h>

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

void resetDisplay()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
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
