/* -*- c++ -*- */
/*
 * Copyright 2025 gr-customModule author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_FILTRO_FIR_CLUSTER_LOG_H
#define INCLUDED_CUSTOMMODULE_FILTRO_FIR_CLUSTER_LOG_H

#include <gnuradio/customModule/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace customModule {

/*!
 * \brief <+description of block+>
 * \ingroup customModule
 *
 */
class CUSTOMMODULE_API filtro_FIR_cluster_log : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<filtro_FIR_cluster_log> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of
     * customModule::filtro_FIR_cluster_log.
     *
     * To avoid accidental use of raw pointers, customModule::filtro_FIR_cluster_log's
     * constructor is in a private implementation
     * class. customModule::filtro_FIR_cluster_log::make is the public interface for
     * creating new instances.
     */
    static sptr make(const std::vector<float>& coef, int num_nodos, int num_muestras_log);
};

} // namespace customModule
} // namespace gr

#endif /* INCLUDED_CUSTOMMODULE_FILTRO_FIR_CLUSTER_LOG_H */
