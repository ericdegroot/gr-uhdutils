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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "log_mboard_sensor_every_n_cc_impl.h"

namespace gr {
  namespace uhdutils {

    log_mboard_sensor_every_n_cc::sptr
    log_mboard_sensor_every_n_cc::make(std::string dev_addr, const char *sensor_name, int n, const char *file_name)
    {
      return gnuradio::get_initial_sptr
        (new log_mboard_sensor_every_n_cc_impl(dev_addr, sensor_name, n, file_name));
    }

    /*
     * The private constructor
     */
    log_mboard_sensor_every_n_cc_impl::log_mboard_sensor_every_n_cc_impl(std::string dev_addr, const char *sensor_name, int n, const char *file_name)
      : gr::sync_block("log_mboard_sensor_every_n_cc",
                       gr::io_signature::make(1, 1, sizeof(gr_complex)),
                       gr::io_signature::make(1, 1, sizeof(gr_complex))),
        d_sensor_name(sensor_name), d_n(n), d_log(file_name), d_count(0), d_sensor_waiting(false)
    {
      if (!d_log.is_open()) {
        throw std::runtime_error("can't open log file");
      }

      d_device = uhd::usrp::multi_usrp::make(dev_addr);
    }

    /*
     * Our virtual destructor.
     */
    log_mboard_sensor_every_n_cc_impl::~log_mboard_sensor_every_n_cc_impl()
    {
      if (d_sensor_future.get_state() == boost::future_state::waiting) {
        d_sensor_future.wait();
      }

      d_sensor_thread.join();

      if (d_log.is_open()) {
        d_log.close();
      }
    }

    std::string
    log_mboard_sensor_every_n_cc_impl::get_sensor_value()
    {
      uhd::sensor_value_t sensor_value(d_device->get_mboard_sensor(d_sensor_name));
      return sensor_value.value;
    }

    void
    log_mboard_sensor_every_n_cc_impl::async_get_sensor_value()
    {
      boost::packaged_task<std::string> pt(boost::bind(&log_mboard_sensor_every_n_cc_impl::get_sensor_value, this)); 
      d_sensor_future = pt.get_future();
      d_sensor_thread = boost::thread(boost::move(pt));
      d_sensor_waiting = true;
    }

    int
    log_mboard_sensor_every_n_cc_impl::work(int noutput_items,
                                            gr_vector_const_void_star &input_items,
                                            gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];

      if (d_sensor_waiting && d_sensor_future.is_ready()) {
        d_log << d_sensor_future.get() << std::endl;
        d_sensor_waiting = false;
      }

      d_count += noutput_items;

      if (d_count >= d_n) {
        if (!d_sensor_waiting) {
          async_get_sensor_value();
        } else {
          std::cerr << "S";
        }

        d_count -= d_n;
      }

      std::memcpy(out, in, noutput_items);

      return noutput_items;
    }

  } /* namespace uhdutils */
} /* namespace gr */

