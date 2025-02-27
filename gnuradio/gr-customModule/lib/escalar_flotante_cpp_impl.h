/* -*- c++ -*- */
/*
 * Copyright 2024 (BORRAR) Luciano.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_ESCALAR_FLOTANTE_CPP_IMPL_H
#define INCLUDED_CUSTOMMODULE_ESCALAR_FLOTANTE_CPP_IMPL_H

#include <gnuradio/customModule/escalar_flotante_cpp.h>

namespace gr {
namespace customModule {

class escalar_flotante_cpp_impl : public escalar_flotante_cpp
{
private:
    float _escalar;

public:
    escalar_flotante_cpp_impl(float escalar);
    ~escalar_flotante_cpp_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace customModule
} // namespace gr

#endif /* INCLUDED_CUSTOMMODULE_ESCALAR_FLOTANTE_CPP_IMPL_H */
