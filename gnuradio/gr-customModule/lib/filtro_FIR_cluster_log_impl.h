/* -*- c++ -*- */
/*
 * Copyright 2025 gr-customModule author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_FILTRO_FIR_CLUSTER_LOG_IMPL_H
#define INCLUDED_CUSTOMMODULE_FILTRO_FIR_CLUSTER_LOG_IMPL_H

#include <gnuradio/customModule/filtro_FIR_cluster_log.h>
#include <stdio.h>
#include <mpi.h>
#include <ctime>

namespace gr {
namespace customModule {

class filtro_FIR_cluster_log_impl : public filtro_FIR_cluster_log
{
private:
    int _num_muestras_log;
    MPI_Comm inter_comm;  // Comunicador para procesos esclavos
    FILE* log = NULL;
    int contador = 0;
    bool registrando_log = true;

public:
    filtro_FIR_cluster_log_impl(const std::vector<float>& coef,
                                int num_nodos,
                                int num_muestras_log);
    ~filtro_FIR_cluster_log_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace customModule
} // namespace gr

#endif /* INCLUDED_CUSTOMMODULE_FILTRO_FIR_CLUSTER_LOG_IMPL_H */
