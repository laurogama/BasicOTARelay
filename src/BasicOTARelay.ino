/*
 * Simple example MQTT client to run on the Itead Studio Sonoff with OTA
 * update support. Subscribes to a topic and watches for a message of
 * either "0" (turn off LED and relay) or "1" (turn on LED and relay)
 *
 * For more information see:
 *   http://www.superhouse.tv/17-home-automation-control-with-sonoff-arduino-openhab-and-mqtt/
 */

#include "BasicOTARelay.h"

void handlePayload(byte * payload, int length){
    String command="";
    payload[length] = '\0';
  String s = String((char*)payload);
    if(s.toInt()>MIN_VALUE && s.toInt()<MAX_VALUE){
        analogWrite(motorSpeed, s.toInt());
    }
    /*// Examine only the first character of the message*/
    /*if(payload[0] == 49)              // Message "1" in ASCII (turn outputs ON)*/
    /*{*/
    /*digitalWrite(ledPin, LOW);      // LED is active-low, so this turns it on*/
    /*digitalWrite(relayPin, HIGH);*/
    /*} else if(payload[0] == 48)       // Message "0" in ASCII (turn outputs OFF)*/
    /*{*/
    /*digitalWrite(ledPin, HIGH);     // LED is active-low, so this turns it off*/
    /*digitalWrite(relayPin, LOW);*/
    /*} else {*/
    /*Serial.println("Unknown value");*/
    /*}*/
}
/**
 * MQTT callback to process messages
 */
void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i=0;i<length;i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
    handlePayload(payload, length);
}

WiFiClient wificlient;
PubSubClient client(wificlient);

/**
 * Attempt connection to MQTT broker and subscribe to command topic
 */
void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect(CLIENT_ID)) {
            Serial.println("connected");
            client.subscribe(mqttTopic);
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

/**
 * Setup
 */
void setup() {
    Serial.begin(115200);
    Serial.println("Booting");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("WiFi begun");
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }
    Serial.println("Proceeding");

    ArduinoOTA.onStart([]() {
            Serial.println("Start");
            });
    ArduinoOTA.onEnd([]() {
            Serial.println("\nEnd");
            });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
            Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
            });
    ArduinoOTA.onError([](ota_error_t error) {
            Serial.printf("Error[%u]: ", error);
            if      (error == OTA_AUTH_ERROR   ) Serial.println("Auth Failed");
            else if (error == OTA_BEGIN_ERROR  ) Serial.println("Begin Failed");
            else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
            else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
            else if (error == OTA_END_ERROR    ) Serial.println("End Failed");
            });
    ArduinoOTA.begin();
    Serial.println("Ready");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    /* Set up the outputs. LED is active-low */
    pinMode(motorDir, OUTPUT);
    pinMode(motorSpeed, OUTPUT);
    digitalWrite(motorDir, HIGH);
    /* Prepare MQTT client */
    client.setServer(broker, 1883);
    client.setCallback(callback);
}

/**
 * Main
 */
void loop() {
    ArduinoOTA.handle();
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.print("Connecting to ");
        Serial.print(ssid);
        Serial.println("...");
        WiFi.begin(ssid, password);

        if (WiFi.waitForConnectResult() != WL_CONNECTED)
            return;
        Serial.println("WiFi connected");
    }

    if (WiFi.status() == WL_CONNECTED) {
        if (!client.connected()) {
            reconnect();
        }
    }

    if (client.connected())
    {
        client.loop();
    }
}
