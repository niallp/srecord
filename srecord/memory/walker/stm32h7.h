//
// srecord - manipulate eprom load files
// Copyright (C) 2012 Peter Miller
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 3 of the License, or (at your
// option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
// for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//

#ifndef SRECORD_MEMORY_WALKER_STM32H7_H
#define SRECORD_MEMORY_WALKER_STM32H7_H

#include <srecord/stm32.h>
#include <srecord/memory/walker.h>

namespace srecord
{

/**
  * The memory_walker_stm32h7 class is a visitor for calculating the FLASH CRC
  * used by the hardware CRC unit on the STM32H7x series of ARM MPUs.
  * It uses the same polynomial (0x04C11DB7) and word-oriented algorithm as the
  * STM32 walker, but with init=0x00000000 and xor_out=0x55555555.
  * http://www.st.com/
  */
class memory_walker_stm32h7:
    public memory_walker
{
public:
    typedef std::shared_ptr<memory_walker_stm32h7> pointer;

    /**
      * The destructor.
      */
    ~memory_walker_stm32h7() override = default;

    /**
      * The create class method is used to create new dynamically
      * allocated instances of this class.
      */
    static pointer create();

    /**
      * The get method is used to get the CRC32 (STM32H7x FLASH) checksum once
      * all memory chunks have been processed by calls to our observe method.
      */
    unsigned get() const;

protected:
    // See base class for documentation.
    void observe(uint32_t, const void *, int) override;

private:
    /**
      * The default constructor.
      * It is private on purpose, use the #create class method instead.
      */
    memory_walker_stm32h7() = default;

    /**
      * The checksum instance variable is used to remember the running
      * state of the CRC32 (STM32H7x FLASH) checksum calculation.
      * init=0x00000000, xor_out=0x55555555
      */
    stm32 checksum{0x00000000, 0x55555555};

public:
    /**
      * The copy constructor.
      */
    memory_walker_stm32h7(const memory_walker_stm32h7 &) = delete;

    /**
      * The assignment operator.
      */
    memory_walker_stm32h7 &operator=(const memory_walker_stm32h7 &) = delete;
};

};

#endif // SRECORD_MEMORY_WALKER_STM32H7_H
