/*
 ** =================================================
 **
 **       Filename:  BasicOTARelay.h
 **
 **    Description:
 **
 **        Version:  1.0
 **        Created:  2017-03-30
 **       Revision:  none
 **       Compiler:  gcc
 **
 **         Author:  laurogama, <lauro.gama@gmail.com>
 **        Company:  FPF Tech
 **
 ** =================================================
*/
#ifndef BASICOTARELAY_H
#define BASICOTARELAY_H


/*DEFINES*/
#define MIN_VALUE   0
#define MAX_VALUE   1024
#define CLIENT_ID "client-1c6adc"         // Client ID to send to the broker
/*INCLUDES*/
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include "ssid_config.h"
/*VARIABLES*/

/* Sonoff Outputs */
const int motorSpeed = D1;  // Active high
const int motorDir = D3;
const int ledPin   = 13;  // Active low

/* MQTT Settings */
const char* mqttTopic = "/test/relay";   // MQTT topic
IPAddress broker(192, 168, 1, 111);       // Address of the MQTT broker

/*PROTOTYPES*/

void handlePayload(byte * payload, int length);
#endif /* !BASICOTARELAY_H */
