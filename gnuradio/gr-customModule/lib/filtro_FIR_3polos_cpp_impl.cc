/* -*- c++ -*- */
/*
 * Copyright 2024 gr-customModule author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "filtro_FIR_3polos_cpp_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace customModule {


using input_type = float;
using output_type = float;
filtro_FIR_3polos_cpp::sptr
filtro_FIR_3polos_cpp::make(float coef0, float coef1, float coef2)
{
    return gnuradio::make_block_sptr<filtro_FIR_3polos_cpp_impl>(coef0, coef1, coef2);
}


/*
 * The private constructor
 */
filtro_FIR_3polos_cpp_impl::filtro_FIR_3polos_cpp_impl(float coef0,
                                                       float coef1,
                                                       float coef2)
    : gr::sync_block("filtro_FIR_3polos_cpp",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
                     gr::io_signature::make(
                         1 /* min outputs */, 1 /*max outputs */, sizeof(output_type)))
{
    set_history(3);
    _coef0 = coef0;
    _coef1 = coef1;
    _coef2 = coef2;
}

/*
 * Our virtual destructor.
 */
filtro_FIR_3polos_cpp_impl::~filtro_FIR_3polos_cpp_impl() {}

int filtro_FIR_3polos_cpp_impl::work(int noutput_items,
                                     gr_vector_const_void_star& input_items,
                                     gr_vector_void_star& output_items)
{
    //auto in = static_cast<const input_type*>(input_items[0])[history()-1];
    const input_type* in = (const input_type*) &((const input_type*) input_items[0])[history()-1];
    auto out = static_cast<output_type*>(output_items[0]);


    for(int i=0; i < noutput_items; i++)
    {
        out[i] = in[i]*_coef0 + in[i-1]*_coef1 + in[i-2]*_coef2;
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace customModule */
} /* namespace gr */
