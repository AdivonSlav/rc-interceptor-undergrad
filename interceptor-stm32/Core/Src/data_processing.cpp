#include "main.h"

#include "data_processing.h"

uint32_t Core::FlightData::m_Pitch = 0;
uint32_t Core::FlightData::m_Roll = 0;
uint32_t Core::FlightData::m_Yaw = 0;
uint32_t Core::FlightData::m_Throttle = 0;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
  if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
    uint16_t captureValue =
        HAL_TIM_ReadCapturedValue(htim, HAL_TIM_ACTIVE_CHANNEL_1);
    Core::FlightData::m_Pitch = captureValue;
  }
}

Core::FlightData::FlightData() {}

const std::string Core::FlightData::FormatToString() {
  std::string formatted = "";
  formatted += std::to_string(m_Throttle) + "," + std::to_string(m_Yaw) + "," +
               std::to_string(m_Pitch) + "," + std::to_string(m_Roll) + "\n";

  return formatted;
}

uint16_t Core::RandomInt16(uint16_t from, uint16_t to) {
  return from + (rand() % (to - from + 1));
}