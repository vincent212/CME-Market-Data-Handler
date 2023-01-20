/*

THIS SOFTWARE IS OPEN SOURCE UNDER THE MIT LICENSE

Copyright 2022 Vincent Maciejewski, Quant Enterprises & M2 Tech
Contact:
v@m2te.ch
mayeski@gmail.com
https://www.linkedin.com/in/vmayeski/
http://m2te.ch/


Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

https://opensource.org/licenses/MIT

*/

#pragma once

#include <array>

namespace m2tech::mdp3
{
    // maximum size of udp message is 65507
    constexpr size_t msgsz = 66000;

    // todo: the buffer needs to be memory pooled

    /**
     * @brief Buffer to store multicast messages
     * 
     */
    struct message_buffer
    {
        uint32_t seqnum;
        std::array<char, msgsz> message;
        size_t len;
    };

}
