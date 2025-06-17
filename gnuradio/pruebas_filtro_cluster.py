#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: Not titled yet
# GNU Radio version: 3.10.5.1

from packaging.version import Version as StrictVersion

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print("Warning: failed to XInitThreads()")

from PyQt5 import Qt
from gnuradio import qtgui
from gnuradio.filter import firdes
import sip
from gnuradio import analog
from gnuradio import blocks
from gnuradio import customModule
from gnuradio import gr
from gnuradio.fft import window
import sys
import signal
from argparse import ArgumentParser
from gnuradio.eng_arg import eng_float, intx
from gnuradio import eng_notation



from gnuradio import qtgui

class pruebas_filtro_cluster(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Not titled yet", catch_exceptions=True)
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Not titled yet")
        qtgui.util.check_set_qss()
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
            pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "pruebas_filtro_cluster")

        try:
            if StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
                self.restoreGeometry(self.settings.value("geometry").toByteArray())
            else:
                self.restoreGeometry(self.settings.value("geometry"))
        except:
            pass

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 24000

        ##################################################
        # Blocks
        ##################################################

        self.qtgui_freq_sink_x_0 = qtgui.freq_sink_f(
            1024, #size
            window.WIN_BLACKMAN_hARRIS, #wintype
            0, #fc
            samp_rate, #bw
            "", #name
            1,
            None # parent
        )
        self.qtgui_freq_sink_x_0.set_update_time(0.10)
        self.qtgui_freq_sink_x_0.set_y_axis((-140), 10)
        self.qtgui_freq_sink_x_0.set_y_label('Relative Gain', 'dB')
        self.qtgui_freq_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, 0.0, 0, "")
        self.qtgui_freq_sink_x_0.enable_autoscale(False)
        self.qtgui_freq_sink_x_0.enable_grid(False)
        self.qtgui_freq_sink_x_0.set_fft_average(1.0)
        self.qtgui_freq_sink_x_0.enable_axis_labels(True)
        self.qtgui_freq_sink_x_0.enable_control_panel(False)
        self.qtgui_freq_sink_x_0.set_fft_window_normalized(False)


        self.qtgui_freq_sink_x_0.set_plot_pos_half(not False)

        labels = ['', '', '', '', '',
            '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "black", "cyan",
            "magenta", "yellow", "dark red", "dark green", "dark blue"]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]

        for i in range(1):
            if len(labels[i]) == 0:
                self.qtgui_freq_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_freq_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_freq_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_freq_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_freq_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_freq_sink_x_0_win = sip.wrapinstance(self.qtgui_freq_sink_x_0.qwidget(), Qt.QWidget)
        self.top_layout.addWidget(self._qtgui_freq_sink_x_0_win)
        self.customModule_filtro_FIR_cluster_log_0_2 = customModule.filtro_FIR_cluster_log([-0.000159218610761937911200758488661222145,-0.000430359456204313154097790272700763126,
        -0.000561775254636760605110590294231087682,-0.000489840873230431607388002390734982328,
        -0.000205138660856850552549265898072405889, 0.000227954566336893634263469077261277107,
         0.000669705996889420770122602899476760285, 0.000935068105496070158151600271168035761,
         0.000857842323225355054411300770311754604, 0.000372230362247760087138215290281095804,
        -0.000422936841594838148356005902428478294,-0.001256902810726467792715177473894527793,
        -0.00176050993133213982619333926038507343,-0.001610306240851903242239373525990231428,
        -0.000693627791860814487019670782075309035, 0.000780061826223386878265131372245377861,
         0.002290297318945717225391334181949787308, 0.003166042258238703412803749515092022193,
         0.002856840920924310581879845827302233374, 0.001213957125391211403289681847184056096,
        -0.001347227131676383658775986162936533219,-0.003905453568825525013236132920724230644,
        -0.005334169728864465893913848759666507249,-0.004759486744479700381926789987119263969,
        -0.002001671381602028627899603208106782404, 0.002200731660298483900045640737630492367,
         0.006326767221708212186881414851313820691, 0.008578929085475365395874192131486779545,
         0.007608160734253766391277373770662961761, 0.003184140060691302911988209700666629942,
        -0.003488248846301648335016531987662347092,-0.010006147282870192505299655749695375562,
        -0.013558745771432336932327267220443900442,-0.012036247337045483454809335910340450937,
        -0.005051693199621982467706349240188501426, 0.005561634076910163329565683909549989039,
         0.016071942561815044658857232207083143294, 0.022002174947367152818555879889572679531,
         0.019799738563965139231948242581893282477, 0.008459138643643174942932105864201730583,
        -0.009529048607261803374712805236868007341,-0.028361213005418703381188549883518135175,
        -0.040333835684212157590700087439472554252,-0.03814868318690734644293982569251966197,
        -0.017415187253869975764208888335815572646, 0.021484629846216300036454427413445955608,
         0.072858429076204614394107750285911606625, 0.126785617373732201196290247935394290835,
         0.171588240707207573265691280539613217115, 0.196987399839038984650230190709407906979,
         0.196987399839038984650230190709407906979, 0.171588240707207573265691280539613217115,
         0.126785617373732201196290247935394290835, 0.072858429076204614394107750285911606625,
         0.021484629846216300036454427413445955608,-0.017415187253869975764208888335815572646,
        -0.03814868318690734644293982569251966197,-0.040333835684212157590700087439472554252,
        -0.028361213005418703381188549883518135175,-0.009529048607261803374712805236868007341,
         0.008459138643643174942932105864201730583, 0.019799738563965139231948242581893282477,
         0.022002174947367152818555879889572679531, 0.016071942561815044658857232207083143294,
         0.005561634076910163329565683909549989039,-0.005051693199621982467706349240188501426,
        -0.012036247337045483454809335910340450937,-0.013558745771432336932327267220443900442,
        -0.010006147282870192505299655749695375562,-0.003488248846301648335016531987662347092,
         0.003184140060691302911988209700666629942, 0.007608160734253766391277373770662961761,
         0.008578929085475365395874192131486779545, 0.006326767221708212186881414851313820691,
         0.002200731660298483900045640737630492367,-0.002001671381602028627899603208106782404,
        -0.004759486744479700381926789987119263969,-0.005334169728864465893913848759666507249,
        -0.003905453568825525013236132920724230644,-0.001347227131676383658775986162936533219,
         0.001213957125391211403289681847184056096, 0.002856840920924310581879845827302233374,
         0.003166042258238703412803749515092022193, 0.002290297318945717225391334181949787308,
         0.000780061826223386878265131372245377861,-0.000693627791860814487019670782075309035,
        -0.001610306240851903242239373525990231428,-0.00176050993133213982619333926038507343,
        -0.001256902810726467792715177473894527793,-0.000422936841594838148356005902428478294,
         0.000372230362247760087138215290281095804, 0.000857842323225355054411300770311754604,
         0.000935068105496070158151600271168035761, 0.000669705996889420770122602899476760285,
         0.000227954566336893634263469077261277107,-0.000205138660856850552549265898072405889,
        -0.000489840873230431607388002390734982328,-0.000561775254636760605110590294231087682,
        -0.000430359456204313154097790272700763126,-0.000159218610761937911200758488661222145], 1, 10000000)
        self.blocks_throttle_0 = blocks.throttle(gr.sizeof_float*1, samp_rate,True)
        self.analog_noise_source_x_0 = analog.noise_source_f(analog.GR_GAUSSIAN, 1, 0)


        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_noise_source_x_0, 0), (self.blocks_throttle_0, 0))
        self.connect((self.blocks_throttle_0, 0), (self.customModule_filtro_FIR_cluster_log_0_2, 0))
        self.connect((self.customModule_filtro_FIR_cluster_log_0_2, 0), (self.qtgui_freq_sink_x_0, 0))


    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "pruebas_filtro_cluster")
        self.settings.setValue("geometry", self.saveGeometry())
        self.stop()
        self.wait()

        event.accept()

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.blocks_throttle_0.set_sample_rate(self.samp_rate)
        self.qtgui_freq_sink_x_0.set_frequency_range(0, self.samp_rate)




def main(top_block_cls=pruebas_filtro_cluster, options=None):

    if StrictVersion("4.5.0") <= StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()

    tb.start()

    tb.show()

    def sig_handler(sig=None, frame=None):
        tb.stop()
        tb.wait()

        Qt.QApplication.quit()

    signal.signal(signal.SIGINT, sig_handler)
    signal.signal(signal.SIGTERM, sig_handler)

    timer = Qt.QTimer()
    timer.start(500)
    timer.timeout.connect(lambda: None)

    qapp.exec_()

if __name__ == '__main__':
    main()
