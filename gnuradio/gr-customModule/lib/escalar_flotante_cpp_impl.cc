/* -*- c++ -*- */
/*
 * Copyright 2024 (BORRAR) Luciano.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "escalar_flotante_cpp_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace customModule {

using input_type = float;
using output_type = float;
escalar_flotante_cpp::sptr escalar_flotante_cpp::make(float escalar)
{
    return gnuradio::make_block_sptr<escalar_flotante_cpp_impl>(escalar);
}


/*
 * The private constructor
 */
escalar_flotante_cpp_impl::escalar_flotante_cpp_impl(float escalar)
    : gr::sync_block("escalar_flotante_cpp",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
                     gr::io_signature::make(
                         1 /* min outputs */, 1 /*max outputs */, sizeof(output_type)))
{
    _escalar = escalar;
}

/*
 * Our virtual destructor.
 */
escalar_flotante_cpp_impl::~escalar_flotante_cpp_impl() {}

int escalar_flotante_cpp_impl::work(int noutput_items,
                                    gr_vector_const_void_star& input_items,
                                    gr_vector_void_star& output_items)
{
    auto in0 = static_cast<const input_type*>(input_items[0]);
    auto out = static_cast<output_type*>(output_items[0]);

    for (int index = 0; index < noutput_items; index++) {
        out[index] = in0[index] * _escalar;
    }
    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace customModule */
} /* namespace gr */
