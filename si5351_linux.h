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

#ifndef SI5351_LINUX_H_
#define SI5351_LINUX_H_

#include <stdint.h>

#include "Si5351Arduino/src/si5351_base.h"
#include "userspace-i2c/src/i2c.h"

/* Linux I2C access to the Si5351 core library */

class Si5351: public Si5351_Base {
public:
  Si5351(uint8_t, uint8_t);
  
protected:
  uint8_t check_address();
  uint8_t si5351_write_bulk(uint8_t, uint8_t, uint8_t *);
  uint8_t si5351_write(uint8_t, uint8_t);
  uint8_t si5351_read(uint8_t);

private:
  I2C *i2c;
  uint8_t adapter_id;
  uint8_t dev_addr;
};

#endif /* SI5351_LINUX_H_ */
