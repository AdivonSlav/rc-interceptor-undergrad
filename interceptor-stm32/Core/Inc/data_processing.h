#pragma once

#include <cstdint>
#include <string>

namespace Core {
class FlightData {
private:
public:
  static uint32_t m_Throttle;
  static uint32_t m_Yaw;
  static uint32_t m_Pitch;
  static uint32_t m_Roll;

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