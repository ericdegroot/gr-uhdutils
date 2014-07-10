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
    log_mboard_sensor_every_n_cc::make(::uhd::usrp::multi_usrp::sptr device, const char *sensor_name, int n, const char *file_name)
    {
      return gnuradio::get_initial_sptr
        (new log_mboard_sensor_every_n_cc_impl(device, sensor_name, n, file_name));
    }

    /*
     * The private constructor
     */
    log_mboard_sensor_every_n_cc_impl::log_mboard_sensor_every_n_cc_impl(::uhd::usrp::multi_usrp::sptr device, const char *sensor_name, int n, const char *file_name)
      : gr::sync_block("log_mboard_sensor_every_n_cc",
                       gr::io_signature::make(1, 1, sizeof(gr_complex)),
                       gr::io_signature::make(1, 1, sizeof(gr_complex))),
        d_device(device), d_sensor_name(sensor_name), d_n(n), d_log(file_name), d_count(0)
    {
      if (!d_log.is_open()) {
        throw std::runtime_error("can't open log file");
      }
    }

    /*
     * Our virtual destructor.
     */
    log_mboard_sensor_every_n_cc_impl::~log_mboard_sensor_every_n_cc_impl()
    {
      if (d_log.is_open()) {
        d_log.close();
      }
    }

    int
    log_mboard_sensor_every_n_cc_impl::work(int noutput_items,
                                            gr_vector_const_void_star &input_items,
                                            gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];
      int output_produced = 0;

      if (d_count + noutput_items >= d_n) {
        uhd::sensor_value_t gps_gpgga_value(d_device->get_mboard_sensor(d_sensor_name));
        d_log << gps_gpgga_value.value << std::endl;

        output_produced = d_n - d_count;
        d_count = 0;
      } else {
        output_produced = noutput_items;
        d_count += noutput_items;
      }

      std::memcpy(out, in, output_produced);

      return output_produced;
    }

  } /* namespace uhdutils */
} /* namespace gr */

