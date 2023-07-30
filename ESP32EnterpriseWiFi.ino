#include <WiFi.h>
#include "esp_wpa2.h" //wpa2 library for connections to Enterprise networks

#define EAP_ANONYMOUS_IDENTITY "identity@organisation.domain"
#define EAP_IDENTITY "identity@organisation.domain" 
#define EAP_PASSWORD "password"

void ConnectEnterpriseWiFi() {
  const char* wpa2e_ssid = "SSID"; // WPA2-Enterprise SSID
  int wpa2e_count = 0;
  delay(10);
  Serial.println();
  Serial.print("Connecting to network: " + String(wpa2e_ssid));
  WiFi.disconnect(true); 
  WiFi.mode(WIFI_STA); 
  WiFi.begin(wpa2e_ssid, WPA2_AUTH_PEAP, EAP_ANONYMOUS_IDENTITY, EAP_IDENTITY, EAP_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    wpa2e_count++;
    if (wpa2e_count >= 60) { //after 30 seconds timeout - reset board
      Serial.println("\nCouldn't get a WiFi connection. Restarting...");
      ESP.restart();
    }
  }
  Serial.println("\nConnected to Enterprise WiFi with IP Address: ");
  Serial.println(WiFi.localIP());
}

void setup(){
  Serial.begin(115200);
  ConnectEnterpriseWiFi();
}

void loop(){ 
  delay(5000);
  Serial.print("Connected Network Signal Strength (RSSI): ");
  Serial.println(WiFi.RSSI());  /*Print WiFi signal strength*/
}
