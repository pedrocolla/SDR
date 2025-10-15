/* -*- c++ -*- */
/*
 * Copyright 2024 UADER-FCyT.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_CUSTOMMODULE_MULTDIVSELECT_H
#define INCLUDED_CUSTOMMODULE_MULTDIVSELECT_H

#include <gnuradio/customModule/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace customModule {

/*!
 * \brief <+description of block+>
 * \ingroup customModule
 *
 */
class CUSTOMMODULE_API multDivSelect : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<multDivSelect> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of customModule::multDivSelect.
     *
     * To avoid accidental use of raw pointers, customModule::multDivSelect's
     * constructor is in a private implementation
     * class. customModule::multDivSelect::make is the public interface for
     * creating new instances.
     */
    static sptr make(bool selector = true);
};

} // namespace customModule
} // namespace gr

#endif /* INCLUDED_CUSTOMMODULE_MULTDIVSELECT_H */
