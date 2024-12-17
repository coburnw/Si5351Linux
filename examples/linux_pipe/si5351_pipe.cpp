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

#include <stdint.h>

#include "si5351_linux.h"

void setup(Si5351 si5351)
{
  bool i2c_found;

  // initialize the Si5351
  i2c_found = si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0);
  if(!i2c_found)
  {
    std::cout << "Device not found on I2C bus!" << std::endl;
  }

}

void print_status(Si5351 si5351){
  // Query a status update and wait a bit to let the Si5351 populate the
  // status flags correctly.
  si5351.update_status();
  sleep(1);
  std::cout << "SYS_INIT: " << std::to_string(si5351.dev_status.SYS_INIT) << std::endl;
  std::cout << "  LOL_A: " << std::to_string(si5351.dev_status.LOL_A) << std::endl;
  std::cout << "  LOL_B: " << std::to_string(si5351.dev_status.LOL_B) << std::endl;
  std::cout << "  LOS: "  << std::to_string(si5351.dev_status.LOS) << std::endl;
  std::cout << "  REVID: " << std::to_string(si5351.dev_status.REVID) << std::endl;
}

int main(int argc, char** argv)
{
  uint8_t buss_id = 1;  // /dev/i2c-1
  uint8_t chip_addr = 0x60;
  
  Si5351 si5351 = Si5351(buss_id, chip_addr);
  
  // the library must be doing some of its own initialization in .init
  si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0);
  
  char* cmd = nullptr;
  uint64_t val = 0ULL;

  // Parse arguments
  if (argc > 1){
    cmd = argv[1];
  }

  if (argc > 2){
    char* end = NULL;
    val = strtoull(argv[2], &end, 10);
  }

  // Act on commands
  if (cmd == nullptr){
    print_status(si5351);
  }
  else if (!strcmp(cmd, "help")){
    std::cout << "cmd <command> <value>" << std::endl;
    std::cout << " where <command> can be:" << std::endl;
    std::cout << "   'help' for this message" << std::endl;
    std::cout << "   'init' to initialize the device" << std::endl;
    std::cout << "   'f0', 'f1', or 'f2' for output frequency in Hz"  << std::endl;
    std::cout << " and <value> is an optional value" << std::endl;
  }
  else if (!strcmp(cmd, "init")){
    setup(si5351);
  }
  else if (!strcmp(cmd, "f0")){
    // Set CLK0
    if (val == 0){
      si5351.output_enable(SI5351_CLK0, 0);
    }
    else{
      si5351.output_enable(SI5351_CLK0, 1);
      si5351.set_freq(val, SI5351_CLK0);
    }
  }
  else if (!strcmp(cmd, "f1")){
    // Set CLK0
    if (val == 0){
      si5351.output_enable(SI5351_CLK1, 0);
    }
    else{
      si5351.output_enable(SI5351_CLK1, 1);
      si5351.set_freq(val, SI5351_CLK1);
    }
  }
  else if (!strcmp(cmd, "f2")){
    // Set CLK0
    if (val == 0){
      si5351.output_enable(SI5351_CLK2, 0);
    }
    else{
      si5351.output_enable(SI5351_CLK2, 1);
      si5351.set_freq(val, SI5351_CLK2);
    }
  }
  
  // Read the Status Register and print it every 10 seconds
  while(false){
    print_status(si5351);
  }

}
