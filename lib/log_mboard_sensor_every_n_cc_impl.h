/* -*- c++ -*- */
/* 
 * Copyright 2014 Eric de Groot (edegroot@email.arizona.edu).
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_UHDUTILS_LOG_MBOARD_SENSOR_EVERY_N_CC_IMPL_H
#define INCLUDED_UHDUTILS_LOG_MBOARD_SENSOR_EVERY_N_CC_IMPL_H

#include <fstream>
#include <string>
#include <boost/thread.hpp>
#include <boost/thread/future.hpp>
#include <uhdutils/log_mboard_sensor_every_n_cc.h>
#include <uhd/usrp/multi_usrp.hpp>

namespace gr {
  namespace uhdutils {

    class log_mboard_sensor_every_n_cc_impl : public log_mboard_sensor_every_n_cc
    {
    private:
      uhd::usrp::multi_usrp::sptr d_device;
      std::string d_sensor_name;
      int d_n;
      std::ofstream d_log;
      int d_count;

      bool d_sensor_waiting;
      boost::thread d_sensor_thread;
      boost::unique_future<std::string> d_sensor_future;

      std::string get_sensor_value();
      void async_get_sensor_value();

    public:
      log_mboard_sensor_every_n_cc_impl(std::string dev_addr, const char *sensor_name, int n, const char *file_name);
      ~log_mboard_sensor_every_n_cc_impl();

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace uhdutils
} // namespace gr

#endif /* INCLUDED_UHDUTILS_LOG_MBOARD_SENSOR_EVERY_N_CC_IMPL_H */
