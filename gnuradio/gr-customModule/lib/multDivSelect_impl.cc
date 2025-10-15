/* -*- c++ -*- */
/*
 * Copyright 2024 UADER-FCyT.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "multDivSelect_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace customModule {

//#pragma message("set the following appropriately and remove this warning")
//using input_type = float;
//#pragma message("set the following appropriately and remove this warning")
//using output_type = float;

using input_type = gr_complex;
using output_type = gr_complex;

multDivSelect::sptr multDivSelect::make(bool selector)
{
    return gnuradio::make_block_sptr<multDivSelect_impl>(selector);
}


/*
 * The private constructor
 */
//multDivSelect_impl::multDivSelect_impl(bool selector)
//    : gr::sync_block("multDivSelect",
//                     gr::io_signature::make(
//                         1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
//                     gr::io_signature::make(
//                         1 /* min outputs */, 1 /*max outputs */, sizeof(output_type)))
//{
//}

multDivSelect_impl::multDivSelect_impl(bool selector)
    : gr::sync_block("multDivSelect",
                     gr::io_signature::make(
                         2 /* min inputs */, 2 /* max inputs */, sizeof(input_type)),
                     gr::io_signature::make(
                         1 /* min outputs */, 1 /*max outputs */, sizeof(output_type)))
{
    _selector = selector;
}

/*
 * Our virtual destructor.
 */
multDivSelect_impl::~multDivSelect_impl() {}

int multDivSelect_impl::work(int noutput_items,
                               gr_vector_const_void_star& input_items,
                               gr_vector_void_star& output_items)
{
    auto in0 = static_cast<const input_type*>(input_items[0]);
    auto in1 = static_cast<const input_type*>(input_items[1]);
    auto out = static_cast<output_type*>(output_items[0]);

    for (int index = 0; index < noutput_items; index++) {
        if (_selector) { out[index] = in0[index] * in1[index]; }
        else{ out[index] = in0[index] / in1[index]; }
    }


    // Tell runtime system how many output items we produced.
    return noutput_items;
}



//int multDivSelect_impl::work(int noutput_items,
//                             gr_vector_const_void_star& input_items,
//                             gr_vector_void_star& output_items)
//{
//    auto in = static_cast<const input_type*>(input_items[0]);
//    auto out = static_cast<output_type*>(output_items[0]);
//
//#pragma message("Implement the signal processing in your block and remove this warning")
//    // Do <+signal processing+>
//
//    // Tell runtime system how many output items we produced.
//    return noutput_items;
//}

} /* namespace customModule */
} /* namespace gr */
