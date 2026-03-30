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

#include <srecord/arglex/tool.h>
#include <srecord/input/filter/message/stm32h7.h>
#include <srecord/memory/walker/stm32h7.h>
#include <srecord/record.h>


srecord::input_filter_message_stm32h7::input_filter_message_stm32h7(
    const input::pointer &a_deeper,
    uint32_t a_address,
    endian_t a_end
) :
    input_filter_message(a_deeper),
    address(a_address),
    end(a_end)
{
}


srecord::input::pointer
srecord::input_filter_message_stm32h7::create(const input::pointer &a_deeper,
    uint32_t a_address, endian_t a_end)
{
    return
        pointer
        (
            new input_filter_message_stm32h7(a_deeper, a_address, a_end)
        );
}


void
srecord::input_filter_message_stm32h7::command_line(arglex_tool *)
{
}


void
srecord::input_filter_message_stm32h7::process(const memory &input,
    record &output)
{
    memory_walker_stm32h7::pointer w = memory_walker_stm32h7::create();
    input.walk(w);
    uint32_t crc = w->get();

    uint8_t chunk[4];
    record::encode(chunk, crc, sizeof(chunk), end);
    output = record(record::type_data, address, chunk, sizeof(chunk));
}


const char *
srecord::input_filter_message_stm32h7::get_algorithm_name()
    const
{
    return "STM32H7x";
}


unsigned
srecord::input_filter_message_stm32h7::get_minimum_alignment()
    const
{
    return 4;
}
