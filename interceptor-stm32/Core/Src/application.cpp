#include "usbd_cdc_if.h"

#include "application.h"
#include "data_processing.h"

void Core::Application::Run() {
  FlightData dataHandle;

  while (true) {
    const std::string dataStr = dataHandle.FormatToString();
    uint8_t *data = (uint8_t *)dataStr.c_str();

    if (CDC_Transmit_FS(data, strlen(dataStr.c_str())) == USBD_OK) {
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
      HAL_Delay(100);
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    } else {
      for (size_t i = 0; i < 10; i++) {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        HAL_Delay(50);
      }
    }

    HAL_Delay(1000);
  }
}