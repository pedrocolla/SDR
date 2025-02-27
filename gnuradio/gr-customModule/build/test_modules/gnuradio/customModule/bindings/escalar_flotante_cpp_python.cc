/*
 * Copyright 2024 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

/***********************************************************************************/
/* This file is automatically generated using bindtool and can be manually edited  */
/* The following lines can be configured to regenerate this file during cmake      */
/* If manual edits are made, the following tags should be modified accordingly.    */
/* BINDTOOL_GEN_AUTOMATIC(0)                                                       */
/* BINDTOOL_USE_PYGCCXML(0)                                                        */
/* BINDTOOL_HEADER_FILE(escalar_flotante_cpp.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(72614f4e4e5067a4b02069e1be5d9509)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/customModule/escalar_flotante_cpp.h>
// pydoc.h is automatically generated in the build directory
#include <escalar_flotante_cpp_pydoc.h>

void bind_escalar_flotante_cpp(py::module& m)
{

    using escalar_flotante_cpp    = gr::customModule::escalar_flotante_cpp;


    py::class_<escalar_flotante_cpp, gr::sync_block, gr::block, gr::basic_block,
        std::shared_ptr<escalar_flotante_cpp>>(m, "escalar_flotante_cpp", D(escalar_flotante_cpp))

        .def(py::init(&escalar_flotante_cpp::make),
           D(escalar_flotante_cpp,make)
        )
        



        ;




}








