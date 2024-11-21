#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"
#include <Base64.h>
#include <ArduinoJson.h>

// Wi-Fi credentials
const char* ssid = "Wifi SSID";
const char* password = "Wifi password";

// GitHub API and Repository
const char* githubToken = "Github token";  
const char* githubRepo = "Path to github repo";
const char* jsonPath = "temperature file name";

// DHT Sensor
#define DHTPIN 19
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);
    dht.begin();

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to Wi-Fi");
}

void loop() {
    float temperature = dht.readTemperature();
    if (!isnan(temperature)) {
        updateGitHubFile(temperature);
    } else {
        Serial.println("Failed to read temperature from sensor.");
    }
    delay(60000); // Send every 1 minute
}

void updateGitHubFile(float temperature) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        String url = "https://api.github.com/repos/" + String(githubRepo) + "/contents/" + jsonPath;
        
        // Get the current SHA of the file to avoid the 409 conflict error
        String sha = getFileSHA(url);

        if (sha.length() > 0) {
            // Prepare the data to be uploaded to GitHub
            String payload = "{\"message\": \"Update temperature\",";
            payload += "\"content\": \"" + encodeBase64("{\"temperature\": " + String(temperature) + "}") + "\",";
            payload += "\"sha\": \"" + sha + "\"}";

            // Send the update request to GitHub
            http.begin(url);
            http.addHeader("Authorization", "token " + String(githubToken));
            http.addHeader("Content-Type", "application/json");

            int httpResponseCode = http.PUT(payload);
            if (httpResponseCode > 0) {
                String response = http.getString();
                Serial.println("Response: " + response);
            } else {
                Serial.println("Error: " + String(httpResponseCode));
            }
            http.end();
        } else {
            Serial.println("Failed to get SHA of the file.");
        }
    } else {
        Serial.println("Wi-Fi not connected");
    }
}

String encodeBase64(String data) {
    const uint8_t* dataPtr = reinterpret_cast<const uint8_t*>(data.c_str());
    String encoded = base64::encode(dataPtr, data.length());
    return encoded;
}

String getFileSHA(String url) {
    HTTPClient http;
    http.begin(url);
    http.addHeader("Authorization", "token " + String(githubToken));

    int httpCode = http.GET();
    String payload = http.getString();
    http.end();

    if (httpCode == 200) {
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, payload);
        return doc["sha"].as<String>();
    } else {
        Serial.println("Error fetching file SHA: " + String(httpCode));
        return "";
    }
}
