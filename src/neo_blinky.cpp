#include "neo_blinky.h"
#include "global.h"

void neo_blinky(void *pvParameters) {
    Adafruit_NeoPixel strip(LED_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);
    strip.begin();
    // Set all pixels to off to start
    strip.clear();
    strip.show();

    while (1)
    {
        // MLResult ml_result;
        SensorData data_receive;
        // if (xQueueReceive(xQueueMLResultforNEO, &ml_result, 0) == pdPASS)
        // {
        //     Serial.print("[NEO] Received from TinyML - Level: ");
        //     Serial.println(ml_result.anomaly_type);

        //     uint32_t color;
        //     String status;
        //     float humidity = ml_result.humidity;

        //     if (ml_result.anomaly_type == "CRITICAL")
        //     {
        //         color = strip.Color(255, 0, 0);
        //         status = "ANOMALY_CRITICAL";
        //     }
        //     else if (ml_result.anomaly_type == "WARNING")
        //     {
        //         color = strip.Color(255, 255, 0);
        //         status = "ANOMALY_WARNING";
        //     }
        //     else
        //     {
        //         if (humidity < 60)
        //         {
        //             color = strip.Color(255, 0, 0);
        //             status = "LOW";
        //         }
        //         else if (humidity < 80)
        //         {
        //             color = strip.Color(0, 255, 0);
        //             status = "NORMAL";
        //         }
        //         else
        //         {
        //             color = strip.Color(0, 0, 255);
        //             status = "WET";
        //         }
        //     }

        //     strip.setPixelColor(0, color);
        //     strip.show();

        //     Serial.print("NeoPixel Update - Status: ");
        //     Serial.println(status);

        //     Serial.print("[NEO] Received from TinyML - Anomaly: ");
        //     Serial.print(ml_result.anomaly_type);
        //     Serial.print(" | Humidity: ");
        //     Serial.print(humidity);
        //     Serial.print("% | Status: ");
        //     Serial.print(status);
        //     Serial.print(" | Color: ");

        //     // In tên màu
        //     if (status == "ANOMALY_CRITICAL") Serial.println("Red");
        //     else if (status == "ANOMALY_WARNING") Serial.println("Yellow");
        //     else if (status == "ERROR") Serial.println("White");
        //     else if (status == "LOW") Serial.println("Red");
        //     else if (status == "NORMAL") Serial.println("Green");
        //     else if (status == "WET") Serial.println("Blue");
        // }
        if (xQueueReceive(xQueueForNeoPixel, &data_receive, portMAX_DELAY) == pdTRUE)
                {
                    float humidity = data_receive.humidity;

                    uint32_t color;
                    String status;

                    if (humidity < 0)
                    {
                        color = strip.Color(255, 255, 255);
                        status = "ERROR";
                    }
                    else if (humidity >= 0 && humidity < 60)
                    {
                        color = strip.Color(255, 0, 0);
                        status = "LOW";
                    }
                    else if (humidity >= 60 && humidity < 80)
                    {
                        color = strip.Color(0, 255, 0);
                        status = "NORMAL";
                    }
                    else if (humidity >= 80)
                    {
                        color = strip.Color(0, 0, 255);
                        status = "WET";
                    }

                    strip.setPixelColor(0, color);
                    strip.show();
                    
                    if(xSemaphoreTake(xSemaphoreMutex, portMAX_DELAY) == pdTRUE)
                    {
                    Serial.print("NeoPixel Update - Humidity: ");
                    Serial.print(humidity);
                    Serial.print("% | Status: ");
                    Serial.print(status);
                    Serial.print(" | Color: ");
                    if (status == "ERROR")
                        Serial.println("White");
                    else if (status == "LOW")
                        Serial.println("Red");
                    else if (status == "NORMAL")
                        Serial.println("Green");
                    else if (status == "WET")
                        Serial.println("Blue");

                    xSemaphoreGive(xSemaphoreMutex);
                    }
                }
            vTaskDelay(100);
    }
}
