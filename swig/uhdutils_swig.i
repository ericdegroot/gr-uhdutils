/* -*- c++ -*- */

#define UHDUTILS_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "uhdutils_swig_doc.i"

%{
#include "uhdutils/log_mboard_sensor_every_n_cc.h"
%}


%include "uhdutils/log_mboard_sensor_every_n_cc.h"
GR_SWIG_BLOCK_MAGIC2(uhdutils, log_mboard_sensor_every_n_cc);
