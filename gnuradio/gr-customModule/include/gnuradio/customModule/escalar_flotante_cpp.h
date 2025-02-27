/* -*- c++ -*- */
/*
 * Copyright 2024 (BORRAR) Luciano.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_ESCALAR_FLOTANTE_CPP_H
#define INCLUDED_CUSTOMMODULE_ESCALAR_FLOTANTE_CPP_H

#include <gnuradio/customModule/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace customModule {

/*!
 * \brief <+description of block+>
 * \ingroup customModule
 *
 */
class CUSTOMMODULE_API escalar_flotante_cpp : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<escalar_flotante_cpp> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of customModule::escalar_flotante_cpp.
     *
     * To avoid accidental use of raw pointers, customModule::escalar_flotante_cpp's
     * constructor is in a private implementation
     * class. customModule::escalar_flotante_cpp::make is the public interface for
     * creating new instances.
     */
    static sptr make(float escalar = 1.0);
};

} // namespace customModule
} // namespace gr

#endif /* INCLUDED_CUSTOMMODULE_ESCALAR_FLOTANTE_CPP_H */
