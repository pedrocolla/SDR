/* -*- c++ -*- */
/*
 * Copyright 2024 gr-customModule author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_HELLO_MPI_GNURADIO_H
#define INCLUDED_CUSTOMMODULE_HELLO_MPI_GNURADIO_H

#include <gnuradio/customModule/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace customModule {

/*!
 * \brief <+description of block+>
 * \ingroup customModule
 *
 */
class CUSTOMMODULE_API hello_mpi_gnuradio : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<hello_mpi_gnuradio> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of customModule::hello_mpi_gnuradio.
     *
     * To avoid accidental use of raw pointers, customModule::hello_mpi_gnuradio's
     * constructor is in a private implementation
     * class. customModule::hello_mpi_gnuradio::make is the public interface for
     * creating new instances.
     */
    static sptr make();
};

} // namespace customModule
} // namespace gr

#endif /* INCLUDED_CUSTOMMODULE_HELLO_MPI_GNURADIO_H */
