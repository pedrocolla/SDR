# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT customModule_sources)
    MESSAGE(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT customModule_sources)

########################################################################
# Check for pygccxml
########################################################################
GR_PYTHON_CHECK_MODULE_RAW(
    "pygccxml"
    "import pygccxml"
    PYGCCXML_FOUND
    )

include(GrPybind)

########################################################################
# Python Bindings
########################################################################
list(APPEND customModule_python_files
    multDivSelect_python.cc
    escalar_flotante_cpp_python.cc
    filtro_FIR_3polos_cpp_python.cc
    filtro_FIR_cpp_python.cc
    hello_mpi_gnuradio_python.cc
    filtro_FIR_cluster_python.cc
    filtro_FIR_cluster_log_python.cc python_bindings.cc)

GR_PYBIND_MAKE_OOT(customModule
   ../../..
   gr::customModule
   "${customModule_python_files}")

# copy bindings extension for use in QA test module
add_custom_command(TARGET customModule_python POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:customModule_python>
    ${PROJECT_BINARY_DIR}/test_modules/gnuradio/customModule/
)

install(TARGETS customModule_python DESTINATION ${GR_PYTHON_DIR}/gnuradio/customModule COMPONENT pythonapi)
