/* -*- c++ -*- */
/*
 * Copyright 2024 gr-customModule author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_FILTRO_FIR_3POLOS_CPP_IMPL_H
#define INCLUDED_CUSTOMMODULE_FILTRO_FIR_3POLOS_CPP_IMPL_H

#include <gnuradio/customModule/filtro_FIR_3polos_cpp.h>

namespace gr {
namespace customModule {

class filtro_FIR_3polos_cpp_impl : public filtro_FIR_3polos_cpp
{
private:
    float _coef0;
    float _coef1;
    float _coef2;

public:
    filtro_FIR_3polos_cpp_impl(float coef0, float coef1, float coef2);
    ~filtro_FIR_3polos_cpp_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace customModule
} // namespace gr

#endif /* INCLUDED_CUSTOMMODULE_FILTRO_FIR_3POLOS_CPP_IMPL_H */
