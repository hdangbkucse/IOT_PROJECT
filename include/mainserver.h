#ifndef __MAIN_SERVER_
#define __MAIN_SERVER_
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "global.h"
#include "taskCoreIOT.h"

#define LED1_PIN 48
#define LED2_PIN 41
#define BOOT_PIN 0
//extern WebServer server;

//extern bool isAPMode;




String mainPage();
String settingsPage();

void startAPmainserver();
void setupServer();
void connectToWiFi();

void main_server_task(void *pvParameters);

#endif