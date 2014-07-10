#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Gps Gpgga
# Generated: Thu Jul 10 09:53:08 2014
##################################################

from gnuradio import analog
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio import uhd
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser
import time
import uhdutils

class gps_gpgga(gr.top_block):

    def __init__(self):
        gr.top_block.__init__(self, "Gps Gpgga")

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 200000
        self.gain = gain = 13
        self.freq = freq = 1270000000
        self.dev_addr = dev_addr = "addr=10.10.10.154"
        self.bw = bw = 10000

        ##################################################
        # Blocks
        ##################################################
        self.uhdutils_log_mboard_sensor_every_n_cc_0 = uhdutils.log_mboard_sensor_every_n_cc(dev_addr, "gps_gpgga", samp_rate, "usrp_gps.dat")
        self.uhd_usrp_sink_0 = uhd.usrp_sink(
        	dev_addr,
        	uhd.stream_args(
        		cpu_format="fc32",
        		channels=range(1),
        	),
        )
        self.uhd_usrp_sink_0.set_samp_rate(samp_rate)
        self.uhd_usrp_sink_0.set_center_freq(freq, 0)
        self.uhd_usrp_sink_0.set_gain(gain, 0)
        self.uhd_usrp_sink_0.set_bandwidth(bw, 0)
        self.analog_sig_source_x_0 = analog.sig_source_c(samp_rate, analog.GR_COS_WAVE, 1000, 1, 0)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_sig_source_x_0, 0), (self.uhdutils_log_mboard_sensor_every_n_cc_0, 0))
        self.connect((self.uhdutils_log_mboard_sensor_every_n_cc_0, 0), (self.uhd_usrp_sink_0, 0))



    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.analog_sig_source_x_0.set_sampling_freq(self.samp_rate)
        self.uhd_usrp_sink_0.set_samp_rate(self.samp_rate)

    def get_gain(self):
        return self.gain

    def set_gain(self, gain):
        self.gain = gain
        self.uhd_usrp_sink_0.set_gain(self.gain, 0)

    def get_freq(self):
        return self.freq

    def set_freq(self, freq):
        self.freq = freq
        self.uhd_usrp_sink_0.set_center_freq(self.freq, 0)

    def get_dev_addr(self):
        return self.dev_addr

    def set_dev_addr(self, dev_addr):
        self.dev_addr = dev_addr

    def get_bw(self):
        return self.bw

    def set_bw(self, bw):
        self.bw = bw
        self.uhd_usrp_sink_0.set_bandwidth(self.bw, 0)

if __name__ == '__main__':
    parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
    (options, args) = parser.parse_args()
    tb = gps_gpgga()
    tb.start()
    raw_input('Press Enter to quit: ')
    tb.stop()
    tb.wait()

