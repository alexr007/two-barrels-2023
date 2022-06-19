#include <Arduino.h>
#include "display.h"
#include "constants.h"
#include "variables.h"

void read_sensors() {
  // hardware pull up, resistor 10K to +5V
  sensor_in_low   = digitalRead(SENSOR_IN_LOW);
  sensor_in_high  = digitalRead(SENSOR_IN_HIGH);
  sensor_out_low  = digitalRead(SENSOR_OUT_LOW);
  sensor_out_high = digitalRead(SENSOR_OUT_HIGH);
}

void pump_on()         { digitalWrite(PUMP_MOTOR, ON);  }
void pump_off()        { digitalWrite(PUMP_MOTOR, OFF); }
void valve_in_open()   { digitalWrite(VALVE_IN,   ON);  }
void valve_in_close()  { digitalWrite(VALVE_IN,   OFF); }
void valve_out_open()  { digitalWrite(VALVE_OUT,  ON);  }
void valve_out_close() { digitalWrite(VALVE_OUT,  OFF); }

bool is_in_full()   { return sensor_in_high  == CLOSED; }
bool is_in_empty()  { return sensor_in_low   == OPENED; }
bool is_out_full()  { return sensor_out_high == CLOSED; }
bool is_out_empty() { return sensor_out_low  == OPENED; }

void stop_in()  { valve_in_close();  is_filling_in  = false; }
void stop_out() { valve_out_close(); is_filling_out = false; }
void fill_in()  { is_filling_in  = true; valve_in_open();  pump_on(); }
void fill_out() { is_filling_out = true; valve_out_open(); pump_on(); }

void do_business() {
    if ( is_in_full()  ) stop_in();
    if ( is_out_full() ) stop_out();
    if (!is_filling_in && !is_filling_out) pump_off();

    if ( is_in_empty()  ) fill_in();
    if ( is_out_empty() ) fill_out();
}

void setup() {
  // sensors
  pinMode (SENSOR_IN_LOW, INPUT);
  pinMode (SENSOR_IN_HIGH, INPUT);
  pinMode (SENSOR_OUT_LOW, INPUT);
  pinMode (SENSOR_OUT_HIGH, INPUT);
  // valves
  pinMode (VALVE_IN, OUTPUT);
  pinMode (VALVE_OUT, OUTPUT);
  pinMode (PUMP_MOTOR, OUTPUT);

  // setup LCD
  lcd.begin(16, 2);

  // all off
  pump_off();
  stop_in();
  stop_out();
}


void display() {
    lcd.setCursor(0,0);
    lcd.print(getLineContent1(sensor_in_low, sensor_in_high, is_filling_in, is_motor_on));
    lcd.setCursor(0,1);
    lcd.print(getLineContent2(sensor_out_low, sensor_out_high, is_filling_out, is_motor_on));
}

void loop() {
    display();
    read_sensors();
//    do_business();
    delay(200);
}