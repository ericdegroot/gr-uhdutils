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


#ifndef INCLUDED_UHDUTILS_LOG_MBOARD_SENSOR_EVERY_N_CC_H
#define INCLUDED_UHDUTILS_LOG_MBOARD_SENSOR_EVERY_N_CC_H

#include <uhdutils/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace uhdutils {

    /*!
     * \brief Logs the mboard sensor value from the given USRP device every N samples.
     * \ingroup uhdutils
     *
     */
    class UHDUTILS_API log_mboard_sensor_every_n_cc : virtual public gr::sync_block
    {
    public:
      typedef boost::shared_ptr<log_mboard_sensor_every_n_cc> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of uhdutils::log_mboard_sensor_every_n_cc.
       *
       * To avoid accidental use of raw pointers, uhdutils::log_mboard_sensor_every_n_cc's
       * constructor is in a private implementation
       * class. uhdutils::log_mboard_sensor_every_n_cc::make is the public interface for
       * creating new instances.
       */
      static sptr make(std::string dev_addr, const char *sensor_name, int n, const char *file_name);
    };

  } // namespace uhdutils
} // namespace gr

#endif /* INCLUDED_UHDUTILS_LOG_MBOARD_SENSOR_EVERY_N_CC_H */
