/* -*- c++ -*- */
/*
 * Copyright 2024 gr-customModule author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "filtro_FIR_cpp_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace customModule {

using input_type = float;
using output_type = float;
filtro_FIR_cpp::sptr filtro_FIR_cpp::make(const std::vector<float>& coef)
{
    return gnuradio::make_block_sptr<filtro_FIR_cpp_impl>(coef);
}


/*
 * The private constructor
 */
filtro_FIR_cpp_impl::filtro_FIR_cpp_impl(const std::vector<float>& coef)
    : gr::sync_block("filtro_FIR_cpp",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
                     gr::io_signature::make(
                         1 /* min outputs */, 1 /*max outputs */, sizeof(output_type))),
    _coef(coef)
{
    set_history(_coef.size()); // Recordar que la función cuenta la muestra actual.
}

/*
 * Our virtual destructor.
 */
filtro_FIR_cpp_impl::~filtro_FIR_cpp_impl() {}

int filtro_FIR_cpp_impl::work(int noutput_items,
                              gr_vector_const_void_star& input_items,
                              gr_vector_void_star& output_items)
{
    const input_type* in = (const input_type*) &((const input_type*) input_items[0])[history()-1];
    auto out = static_cast<output_type*>(output_items[0]);


    for(int i=0; i < noutput_items; i++)
    {
        for(unsigned int j=0; j < _coef.size(); j++)
        {
            out[i] += in[i-j] *_coef[j];
        }
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace customModule */
} /* namespace gr */
