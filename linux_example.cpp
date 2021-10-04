/*
 * si5351_example.ino - Simple example of using Si5351Arduino library
 *
 * Copyright (C) 2015 - 2016 Jason Milldrum <milldrum@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

//#include "userspace-I2C/src/i2c.h"
#include "LinuxInterface.h"
#include "Si5351Arduino/src/si5351.h"

void setup(Si5351 si5351)
{
  bool i2c_found;

  // Start serial and initialize the Si5351
  //Serial.begin(57600);
  i2c_found = si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0);
  if(!i2c_found)
  {
    std::cout << "Device not found on I2C bus!" << std::endl;
  }

  // Set CLK0 to output 14 MHz
  si5351.set_freq(1400000000ULL, SI5351_CLK0);

  // Set CLK1 to output 175 MHz
  si5351.set_ms_source(SI5351_CLK1, SI5351_PLLB);
  si5351.set_freq_manual(17500000000ULL, 70000000000ULL, SI5351_CLK1);

  // Query a status update and wait a bit to let the Si5351 populate the
  // status flags correctly.
  si5351.update_status();
  sleep(0.500);
}

int main()
{
  uint8_t buss_id = 1;
  uint8_t chip_addr = 0x60;
  
  I2CInterface *i2c = new LinuxInterface(buss_id, chip_addr);
  Si5351 si5351 = Si5351(chip_addr, i2c);

  
  setup(si5351);
  
  // Read the Status Register and print it every 10 seconds
  while(true){
    si5351.update_status();
    std::cout << "SYS_INIT: " << std::to_string(si5351.dev_status.SYS_INIT) << std::endl;
    std::cout << "  LOL_A: " << std::to_string(si5351.dev_status.LOL_A) << std::endl;
    std::cout << "  LOL_B: " << std::to_string(si5351.dev_status.LOL_B) << std::endl;
    std::cout << "  LOS: "  << std::to_string(si5351.dev_status.LOS) << std::endl;
    std::cout << "  REVID: " << std::to_string(si5351.dev_status.REVID) << std::endl;

    sleep(5);
  }

}
