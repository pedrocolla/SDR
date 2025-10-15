/* -*- c++ -*- */
/*
 * Copyright 2024 gr-customModule author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_FILTRO_FIR_CPP_IMPL_H
#define INCLUDED_CUSTOMMODULE_FILTRO_FIR_CPP_IMPL_H

#include <gnuradio/customModule/filtro_FIR_cpp.h>

namespace gr {
namespace customModule {

class filtro_FIR_cpp_impl : public filtro_FIR_cpp
{
private:
    const std::vector<float> _coef;

public:
    filtro_FIR_cpp_impl(const std::vector<float>& coef);
    ~filtro_FIR_cpp_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace customModule
} // namespace gr

#endif /* INCLUDED_CUSTOMMODULE_FILTRO_FIR_CPP_IMPL_H */
