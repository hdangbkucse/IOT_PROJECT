#include "task_wifi.h"

void startAPinWIFI()
{
    WiFi.mode(WIFI_AP);
    WiFi.softAP(String(SSID_AP), String(PASS_AP));
    Serial.print("AP IP: ");
    Serial.println(WiFi.softAPIP());
}

void startSTA()
{
    Serial.println("Connecting to AP ...");
    if (wifi_ssid.isEmpty())
    {
        vTaskDelete(NULL);
    }

    WiFi.mode(WIFI_STA);

    if (wifi_password.isEmpty())
    {
        WiFi.begin(wifi_ssid.c_str());
    }
    else
    {
        Serial.println(wifi_ssid.c_str());
        Serial.println(wifi_password.c_str());
        WiFi.begin(wifi_ssid.c_str(), wifi_password.c_str());
    }

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    Serial.println("Connected to AP");
    //Give a semaphore here
    // xSemaphoreGive(xBinarySemaphoreInternet);
}

bool Wifi_reconnect()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        return true;
    }
    startSTA();
    return false;
}
