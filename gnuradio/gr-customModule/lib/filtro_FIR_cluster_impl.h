/* -*- c++ -*- */
/*
 * Copyright 2024 gr-customModule author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_FILTRO_FIR_CLUSTER_IMPL_H
#define INCLUDED_CUSTOMMODULE_FILTRO_FIR_CLUSTER_IMPL_H

#include <gnuradio/customModule/filtro_FIR_cluster.h>

namespace gr {
namespace customModule {

class filtro_FIR_cluster_impl : public filtro_FIR_cluster
{
private:
    int _num_nodos;

public:
    filtro_FIR_cluster_impl(const std::vector<float>& coef, int num_nodo);
    ~filtro_FIR_cluster_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace customModule
} // namespace gr

#endif /* INCLUDED_CUSTOMMODULE_FILTRO_FIR_CLUSTER_IMPL_H */
