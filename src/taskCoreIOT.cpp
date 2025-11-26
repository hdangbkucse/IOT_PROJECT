#include "taskCoreIOT.h"

// bool attributesChanged = false;
SensorData data_receive;


// RPC_Response setLedSwitchState(const RPC_Data &data) {
//     Serial.println("Received Switch state");
//     bool newState = data;    // parse RPC data as bool
//     Serial.print("Switch state change: ");
//     Serial.println(newState);

//     digitalWrite(LED_PIN, newState);
//     attributesChanged = true;

//     return RPC_Response("setLedSwitchValue", newState);
// }

// // Create callback array
// const std::array<RPC_Callback, 1U> callbacks = {
//     RPC_Callback{ "setLedSwitchValue", setLedSwitchState }
// };

void taskCoreIOT(void *pvParameters) {
  pinMode(LED_PIN, OUTPUT);
  xQueueReceive(xQueueForCoreIOT, &data_receive, portMAX_DELAY);

  while(1) {
    float temperature, humidity;
    if(xQueueReceive(xQueueForCoreIOT, &data_receive, portMAX_DELAY) == pdTRUE) {
      temperature = data_receive.temperature;
      humidity = data_receive.humidity;
    }
    if(!isWifiConnected) {
      Wifi_reconnect();
    }
    CORE_IOT_reconnect();
    CORE_IOT_sendata("telemetry", "temperature", String(temperature));
    CORE_IOT_sendata("telemetry", "humidity", String(humidity));
    if (attributesChanged) {
      CORE_IOT_sendata("attribute", "ledState", String(digitalRead(LED_PIN)));
      attributesChanged = false;
    }
    vTaskDelay(5000);
  }
}