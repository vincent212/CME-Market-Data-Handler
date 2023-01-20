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

#include "MessageProcessor.hpp"
#include "RecoveryProcessor.hpp"
#include "CallBackImpl.hpp"

#include <thread>

/**
 * @brief Example program of how to instantiate and run the handler.
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{

  CallBackImpl callback_impl;

  constexpr auto group_a = "233.158.8.17";
  constexpr auto port_a = 14344;
  constexpr auto group_b = "233.158.8.144";
  constexpr auto port_b = 15344;
  constexpr auto group_dr = "224.0.25.191";
  constexpr auto port_dr = 21344;
  constexpr auto group_ir = "233.158.8.101";
  constexpr auto port_ir = 6344;
  constexpr auto mdinterface = "10.248.146.89";

  m2tech::mdp3::MessageProcessor msg_proc(
      &callback_impl,
      port_a,
      port_b,
      group_a,
      group_b,
      mdinterface,
      true,
      true,
      true);

  m2tech::mdp3::RecoveryProcessor<m2tech::mdp3::MessageProcessor> rec_proc(
      &msg_proc,
      &callback_impl,
      port_dr,
      port_ir,
      group_dr,
      group_ir,
      mdinterface,
      true);

  msg_proc.set_recovery_processor(&rec_proc);
  msg_proc.connect();

  std::thread msg_thread(std::ref(msg_proc));
  std::thread rec_thread(std::ref(rec_proc));

  msg_thread.join();
  rec_thread.join();
}
