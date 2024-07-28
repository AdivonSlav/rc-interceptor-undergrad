#include "main.h"

#include "data_processing.h"

TIM_HandleTypeDef *Core::Timers::s_HardwareTimer1 = nullptr;
TIM_HandleTypeDef *Core::Timers::s_HardwareTimer2 = nullptr;
TIM_HandleTypeDef *Core::Timers::s_HardwareTimer3 = nullptr;
TIM_HandleTypeDef *Core::Timers::s_HardwareTimer4 = nullptr;

uint32_t Core::FlightData::s_Pitch = 0;
uint32_t Core::FlightData::s_Roll = 0;
uint32_t Core::FlightData::s_Yaw = 0;
uint32_t Core::FlightData::s_Throttle = 0;
uint32_t Core::FlightData::s_Frequency = 0;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
  if (htim == Core::Timers::s_HardwareTimer1) {
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
      uint32_t ch1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

      if (ch1) {
        float frequency = Core::CalculatePWMFrequency(ch1);
        Core::FlightData::s_Frequency = frequency;

        uint32_t ch2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
        float dutyCycle = Core::CalculatePWMDutyCycle(ch1, ch2);
        Core::FlightData::s_Pitch = dutyCycle;
      }
    }
  }

  if (htim == Core::Timers::s_HardwareTimer2) {
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
      uint32_t ch1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

      if (ch1) {
        float frequency = Core::CalculatePWMFrequency(ch1);
        Core::FlightData::s_Frequency = frequency;

        uint32_t ch2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
        float dutyCycle = Core::CalculatePWMDutyCycle(ch1, ch2);
        Core::FlightData::s_Roll = dutyCycle;
      }
    }
  }

  if (htim == Core::Timers::s_HardwareTimer3) {
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
      uint32_t ch1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

      if (ch1) {
        float frequency = Core::CalculatePWMFrequency(ch1);
        Core::FlightData::s_Frequency = frequency;

        uint32_t ch2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
        float dutyCycle = Core::CalculatePWMDutyCycle(ch1, ch2);
        Core::FlightData::s_Yaw = dutyCycle;
      }
    }
  }

  if (htim == Core::Timers::s_HardwareTimer4) {
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
      uint32_t ch1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

      if (ch1) {
        float frequency = Core::CalculatePWMFrequency(ch1);
        Core::FlightData::s_Frequency = frequency;

        uint32_t ch2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
        float dutyCycle = Core::CalculatePWMDutyCycle(ch1, ch2);
        Core::FlightData::s_Throttle = dutyCycle;
      }
    }
  }
}

float Core::CalculatePWMFrequency(uint32_t ch1) {
  uint32_t clockFreq = HAL_RCC_GetPCLK2Freq();

  return (float)clockFreq / (ch1 + 1);
}

float Core::CalculatePWMDutyCycle(uint32_t ch1, uint32_t ch2) {
  return (float)1000.0f * ch2 / ch1;
}

int32_t Core::Map(int32_t input, int32_t fromMin, int32_t fromMax,
                  int32_t toMin, int32_t toMax) {
  return (input - fromMin) * (toMax - toMin) / (fromMax - fromMin) + toMin;
}

void Core::Timers::SetTimers(TIM_HandleTypeDef *htim1, TIM_HandleTypeDef *htim2,
                             TIM_HandleTypeDef *htim3,
                             TIM_HandleTypeDef *htim4) {
  Core::Timers::s_HardwareTimer1 = htim1;
  Core::Timers::s_HardwareTimer2 = htim2;
  Core::Timers::s_HardwareTimer3 = htim3;
  Core::Timers::s_HardwareTimer4 = htim4;
}

Core::FlightData::FlightData() {}

const std::string Core::FlightData::FormatToString() {
  std::string formatted = "";

  std::string pitchStr = std::to_string(s_Pitch);
  std::string rollStr = std::to_string(s_Roll);
  std::string yawStr = std::to_string(s_Yaw);
  std::string throttleStr = std::to_string(s_Throttle);
  std::string freqStr = std::to_string(s_Frequency);

  formatted += pitchStr + "," + rollStr + "," + yawStr + "," + throttleStr +
               "," + freqStr + "\n";
  return formatted;
}

uint16_t Core::RandomInt16(uint16_t from, uint16_t to) {
  return from + (rand() % (to - from + 1));
}