
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <SPI.h>
#include <WiFi.h>
#include <BlynkSimpleWifi.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "bf366fe494ce48e992c612435204b43e";

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth,"Black airways2","usecondom");
  // Or specify server using one of those commands:
  //Blynk.begin(auth, "yourNetwork", "yourPassword", "server.org", 8442);
  //Blynk.begin(auth, "yourNetwork", "yourPassword", server_ip, port);
}

void loop()
{
  Blynk.run();
}

