#include "usbd_cdc_if.h"

#include "application.h"
#include "data_processing.h"

void Core::Application::Run() {
  uint32_t seedTick = HAL_GetTick();
  srand(seedTick);

  // uint16_t randomThrottle = 0;
  // uint16_t randomYaw = 0;
  // uint16_t randomPitch = 0;
  // uint16_t randomRoll = 0;

  while (true) {
    /*
    randomThrottle = RandomInt16(1100, 1900);
    randomYaw = RandomInt16(1100, 1900);
    randomPitch = RandomInt16(1100, 1900);
    randomRoll = RandomInt16(1100, 1900);
    */

    FlightData dataHandle;
    const std::string dataStr = dataHandle.FormatToString();
    const char *dataCstr = dataStr.c_str();

    if (CDC_Transmit_FS((uint8_t *)dataCstr, strlen(dataCstr)) == USBD_OK) {
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