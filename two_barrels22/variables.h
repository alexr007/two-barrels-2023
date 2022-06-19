#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// current sensor status
unsigned int sensor_in_low;
unsigned int sensor_in_high;
unsigned int sensor_out_low;
unsigned int sensor_out_high;

// current valve status
bool is_filling_in  = false;
bool is_filling_out = false;
bool is_motor_on    = false;
