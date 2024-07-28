#pragma once

#include <cstdint>
#include <string>

namespace Core {

float CalculatePWMFrequency(uint32_t ch1);

float CalculatePWMDutyCycle(uint32_t ch1, uint32_t ch2);

int32_t Map(int32_t input, int32_t fromMin, int32_t fromMax, int32_t toMin,
            int32_t toMax);

class Timers {
private:
public:
  static TIM_HandleTypeDef *s_HardwareTimer1;
  static TIM_HandleTypeDef *s_HardwareTimer2;
  static TIM_HandleTypeDef *s_HardwareTimer3;
  static TIM_HandleTypeDef *s_HardwareTimer4;

  static void SetTimers(TIM_HandleTypeDef *htim1, TIM_HandleTypeDef *htim2,
                        TIM_HandleTypeDef *htim3, TIM_HandleTypeDef *htim4);
};

class FlightData {
private:
public:
  static uint32_t s_Throttle;
  static uint32_t s_Yaw;
  static uint32_t s_Pitch;
  static uint32_t s_Roll;
  static uint32_t s_Frequency;

  FlightData();
  FlightData(const FlightData &obj) = delete;
  FlightData(FlightData &&obj) = delete;

  /// @brief Formats the flight data as a string for transmission
  /// @return The formatted flight data
  const std::string FormatToString();
};

/// @brief Generate a random 16-bit integer
/// @param from Lower boundary
/// @param to Upper boundary
/// @return The random integer
uint16_t RandomInt16(uint16_t from, uint16_t to);
} // namespace Core