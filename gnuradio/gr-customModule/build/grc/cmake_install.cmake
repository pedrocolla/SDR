# Install script for directory: /srv/clusterfs/sdr/gnuradio/gr-customModule/grc

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gnuradio/grc/blocks" TYPE FILE FILES
    "/srv/clusterfs/sdr/gnuradio/gr-customModule/grc/customModule_addSubSelect.block.yml"
    "/srv/clusterfs/sdr/gnuradio/gr-customModule/grc/customModule_multDivSelect.block.yml"
    "/srv/clusterfs/sdr/gnuradio/gr-customModule/grc/customModule_escalar_flotante.block.yml"
    "/srv/clusterfs/sdr/gnuradio/gr-customModule/grc/customModule_escalar_flotante_cpp.block.yml"
    "/srv/clusterfs/sdr/gnuradio/gr-customModule/grc/customModule_filtro_FIR_3polos_cpp.block.yml"
    "/srv/clusterfs/sdr/gnuradio/gr-customModule/grc/customModule_filtro_FIR_cpp.block.yml"
    "/srv/clusterfs/sdr/gnuradio/gr-customModule/grc/customModule_hello_mpi_gnuradio.block.yml"
    "/srv/clusterfs/sdr/gnuradio/gr-customModule/grc/customModule_filtro_FIR_cluster.block.yml"
    "/srv/clusterfs/sdr/gnuradio/gr-customModule/grc/customModule_filtro_FIR_cluster_log.block.yml"
    )
endif()

