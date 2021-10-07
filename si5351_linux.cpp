/*
 * si5351_linux.cpp - Linux interface to the etherkit Si5351 library
 *
 * Copyright (C) 2021 Coburn Wightman
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

#include <stdint.h>

#include "si5351_linux.h"
#include "userspace-i2c/src/i2c.h"

/**
 * The Linux userspace way of talking to I2C
 */

/* 
 * constructor
 * adapter_id: is the numerical id of the i2c interface to use.
 *     if the required interface is named /dev/i2c-1, then set adatper_id = 1
 * device_address: is the address of the si5351 device on the i2c bus, typically 0x60
*/
Si5351::Si5351(uint8_t adapter_id, uint8_t device_address)
{
  dev_addr = device_address;
  i2c = new I2C(adapter_id, dev_addr);    
}

// remaining functions are protected and called by the base class
uint8_t Si5351::check_address()
{
  int32_t result = i2c->read_byte(0);
  if (result < 0)
    return 4;  // Wire 'other error'
  
  return 0; //success
}

uint8_t Si5351::si5351_write_bulk(uint8_t address, uint8_t count, uint8_t *data)
{
  int result = i2c->write_bulk(address, data, count);
  if (result < 0)
    return 4;
  
  return 0;
}

uint8_t Si5351::si5351_write(uint8_t address, uint8_t data)
{
  int result = i2c->write_byte(address, data);
  if (result < 0)
    return 4;
  
  return 0;
}

uint8_t Si5351::si5351_read(uint8_t register_address)
{
  int32_t result = i2c->read_byte(register_address);
  if (result < 0)
    return 0; // verify this
  
  return result;
}
