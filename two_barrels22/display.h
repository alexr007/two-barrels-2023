#include <Arduino.h>
#include "constants.h"

// result is String with length of 4
String intToReadable(unsigned int value) {
  int digit1 = value / 100;
  int digit2 = (value % 100) / 10;
  int digit3 = value % 10;
  return String(digit1) +"." + String(digit2) + String(digit3);
}

String sensor_to_char(unsigned int value) {
  return value == OPENED ? "o" : "x";
}

String valve_to_char(unsigned int value) {
  return value ? "v" : "x";
}

String motor_to_char(unsigned int value) {
  return value ? "M" : " ";
}

String getLineContent1(unsigned int lo, unsigned int hi, bool valve, bool motor) {
  return "I L:" + sensor_to_char(lo) +
          " H:" + sensor_to_char(hi) +
          " V:" + valve_to_char(valve) +
          "  "  + motor_to_char(motor);
}

String getLineContent2(unsigned int lo, unsigned int hi, bool valve, bool motor) {
    return "O L:" + sensor_to_char(lo) +
           " H:" + sensor_to_char(hi) +
           " V:" + valve_to_char(valve) +
           "  "  + motor_to_char(motor);
}
