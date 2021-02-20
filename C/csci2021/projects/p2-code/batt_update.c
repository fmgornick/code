#include <stdio.h>
#include "batt.h"

// array of int representations of 7 bit patterns
int pattern[10] = {63,3,109,103,83,118,126,35,127,119};

int set_batt_from_ports(batt_t *batt) {
  // voltage can't be negative so it returns a 1
  if (BATT_VOLTAGE_PORT < 0) return 1;

  // converts half mlvolts to mlvolts
  batt->mlvolts = BATT_VOLTAGE_PORT / 2;

  int percent = (batt->mlvolts-3000) / 8;
  // makes sure percent field is between 0 and 100
  if (percent < 0) batt->percent = 0;
  else if (percent > 100) batt->percent = 100;
  else batt->percent = percent;

  // check if second bit is one or zero
  batt->mode = ((0b0100 & BATT_STATUS_PORT) >> 2) + 1;

  return 0;
}

int set_display_from_batt(batt_t batt, int *display) {
  int mask;
  // volt setting
  if (batt.mode == 1) {
    // sets volt and decimal to 1 (0b11 = 3)
    mask = 3 << 22;
    // get a 3 digit number of the voltage
    int volts = batt.mlvolts / 10;
    // round up if need be
    if ((batt.mlvolts % 10) >= 5) volts++;

    // take each digit and set it's corresponding 7 bit field
    for (int i=0; i<3; i++) {
      mask = mask | (pattern[volts % 10] << 7*i);
      volts /= 10;
    }
  }

  else {
    // set percentage to 1
    mask = 1 << 21;
    int percent = batt.percent;

    // take each digit and set it's corresponding 7 bit field
    for (int i=0; i<3; i++) {
      mask = mask | (pattern[percent % 10] << 7*i);
      percent /= 10;
    }

    // swap zeros with blanks
    if (batt.percent < 100) mask = mask & ~(pattern[0] << 14);
    if (batt.percent < 10) mask = mask & ~(pattern[0] << 7);
  }

  // fill the correct areas on the battery
  if (batt.percent >= 5) mask = mask | 1 << 24;
  if (batt.percent >= 30) mask = mask | 1 << 25;
  if (batt.percent >= 50) mask = mask | 1 << 26;
  if (batt.percent >= 70) mask = mask | 1 << 27;
  if (batt.percent >= 90) mask = mask | 1 << 28;

  *display = mask;
  return 0;
}

int batt_update() {
  // initialize battery
  batt_t b = { .mlvolts = 0, .percent = 0, .mode = 0 };
  // check if negative voltage, do nothing if 1 is returned
  if (set_batt_from_ports(&b) == 1) return 1;
  set_display_from_batt(b,&BATT_DISPLAY_PORT);
  return 0;
}
