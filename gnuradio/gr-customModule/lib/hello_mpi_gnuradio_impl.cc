/* -*- c++ -*- */
/*
 * Copyright 2024 gr-customModule author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "hello_mpi_gnuradio_impl.h"
#include <gnuradio/io_signature.h>
//#include <stdio.h>
#include <mpi.h>

namespace gr {
namespace customModule {

using input_type = float;
using output_type = float;
hello_mpi_gnuradio::sptr hello_mpi_gnuradio::make()
{
    return gnuradio::make_block_sptr<hello_mpi_gnuradio_impl>();
}


/*
 * The private constructor
 */
hello_mpi_gnuradio_impl::hello_mpi_gnuradio_impl()
    : gr::sync_block("hello_mpi_gnuradio",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
                     gr::io_signature::make(
                         1 /* min outputs */, 1 /*max outputs */, sizeof(output_type)))
{
    char cpuname[20];
    int  cpulen;
    MPI_Init(NULL, NULL);

    //MPI_Comm_rank(MPI_COMM_WORLD, &node);
    MPI_Get_processor_name( cpuname, &cpulen );
    
    printf("[%s] Saludos desde el maesro!\n", cpuname);
    
    MPI_Comm inter_comm;  // Comunicador para procesos esclavos
    MPI_Comm_spawn("/clusterfs/sdr/lib/hello_mpi/hello_mpi_slave", MPI_ARGV_NULL, 3, MPI_INFO_NULL, 0, MPI_COMM_SELF, &inter_comm, MPI_ERRCODES_IGNORE);
}

/*
 * Our virtual destructor.
 */
hello_mpi_gnuradio_impl::~hello_mpi_gnuradio_impl() 
{
    MPI_Finalize();
}

int hello_mpi_gnuradio_impl::work(int noutput_items,
                                  gr_vector_const_void_star& input_items,
                                  gr_vector_void_star& output_items)
{
    auto in = static_cast<const input_type*>(input_items[0]);
    auto out = static_cast<output_type*>(output_items[0]);

    for (int i = 0; i < noutput_items; i++)
    {
        out[i] = in[i];
    }
    

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace customModule */
} /* namespace gr */
