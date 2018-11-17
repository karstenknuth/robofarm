#include "DHT.h"
#include "Constants.h"
#include "ArduinoUtil.h"
#include "RobofarmWifiClient.h"

#define DHTPIN 4  // what digital pin the DHT22 is conected to
#define DHTTYPE DHT22 // there are multiple kinds of DHT sensors

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  ArduinoUtil::initSerial(115200);
  RobofarmWifiClient::connectToWifi(ssid, password);
}

int timeSinceLastRead = 0;
void loop() {

  // Report every 2 seconds.
  if(timeSinceLastRead > 10000) {
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      timeSinceLastRead = 0;
      return;
    }
    
    // Compute heat index in Celsius (isFahreheit = false)
    float hic = dht.computeHeatIndex(t, h, false);

    // We now create a URI for the request
    String url = "/dht";
    url += "?temperature=";
    url += temperature;
    url += "&humidity=";
    url += humidity;
    url += "&heat_index=";
    url += heatIndex;

    RobofarmWifiClient::postData(url);

    timeSinceLastRead = 0;
  }
  delay(10000);
  timeSinceLastRead += 10000;
}

