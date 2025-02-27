#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2024 BORRAR-Luciano.
#
# SPDX-License-Identifier: GPL-3.0-or-later
#


import numpy as np
from gnuradio import gr

class escalar_flotante(gr.sync_block):
    """
    docstring for block escalar_flotante
    """
    def __init__(self, escalar=1.0):
        gr.sync_block.__init__(self,
            name="escalar_flotante",
            in_sig=[np.float32],
            out_sig=[np.float32])
        self.escalar = escalar

    def work(self, input_items, output_items):
        in0 = input_items[0]
        out = output_items[0]
        # <+signal processing here+>
        out[:] = in0*self.escalar
        return len(output_items[0])
