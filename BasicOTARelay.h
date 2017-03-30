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
/*INCLUDES*/
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>
/*VARIABLES*/
/*PROTOTYPES*/

void handlePayload(byte * payload, int length);
#endif /* !BASICOTARELAY_H */
