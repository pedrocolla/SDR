/* -*- c++ -*- */
/*
 * Copyright 2024 gr-customModule author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_HELLO_MPI_GNURADIO_IMPL_H
#define INCLUDED_CUSTOMMODULE_HELLO_MPI_GNURADIO_IMPL_H

#include <gnuradio/customModule/hello_mpi_gnuradio.h>

namespace gr {
namespace customModule {

class hello_mpi_gnuradio_impl : public hello_mpi_gnuradio
{
private:
    // Nothing to declare in this block.
    
public:
    hello_mpi_gnuradio_impl();
    ~hello_mpi_gnuradio_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace customModule
} // namespace gr

#endif /* INCLUDED_CUSTOMMODULE_HELLO_MPI_GNURADIO_IMPL_H */
