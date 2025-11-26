#include "global.h"
//float glob_temperature = 0;
//float glob_humidity = 0;


String WIFI_SSID = "xiaolin";
String WIFI_PASS = "haolatao";
String CORE_IOT_TOKEN = "1soz6w0m02s3ma7qza2s";
String CORE_IOT_SERVER = "app.coreiot.io";
String CORE_IOT_PORT = "1883U";

String ssid = "ESPRE!!!";
String password = "12345678";
String wifi_ssid = "";
String wifi_password = "";
boolean isWifiConnected = false;

SensorData sensordata;
SemaphoreHandle_t xBinarySemaphoreData = xSemaphoreCreateMutex();
SemaphoreHandle_t xBinarySemaphoreInternet = xSemaphoreCreateBinary();
SemaphoreHandle_t xSemaphoreMutex = xSemaphoreCreateMutex();

QueueHandle_t xQueueForLedBlink = xQueueCreate(5, sizeof(SensorData));
QueueHandle_t xQueueForNeoPixel = xQueueCreate(5, sizeof(SensorData));
QueueHandle_t xQueueForTinyML   = xQueueCreate(5, sizeof(SensorData));
QueueHandle_t xQueueForCoreIOT   = xQueueCreate(1, sizeof(SensorData));
QueueHandle_t xQueueForMainServer   = xQueueCreate(5, sizeof(SensorData));