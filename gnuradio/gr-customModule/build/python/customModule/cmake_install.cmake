# Install script for directory: /srv/clusterfs/sdr/gnuradio/gr-customModule/python/customModule

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python3.11/dist-packages/gnuradio/customModule" TYPE FILE FILES
    "/srv/clusterfs/sdr/gnuradio/gr-customModule/python/customModule/__init__.py"
    "/srv/clusterfs/sdr/gnuradio/gr-customModule/python/customModule/addSubSelect.py"
    "/srv/clusterfs/sdr/gnuradio/gr-customModule/python/customModule/escalar_flotante.py"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python3.11/dist-packages/gnuradio/customModule" TYPE FILE FILES
    "/srv/clusterfs/sdr/gnuradio/gr-customModule/build/python/customModule/__init__.pyc"
    "/srv/clusterfs/sdr/gnuradio/gr-customModule/build/python/customModule/addSubSelect.pyc"
    "/srv/clusterfs/sdr/gnuradio/gr-customModule/build/python/customModule/escalar_flotante.pyc"
    "/srv/clusterfs/sdr/gnuradio/gr-customModule/build/python/customModule/__init__.pyo"
    "/srv/clusterfs/sdr/gnuradio/gr-customModule/build/python/customModule/addSubSelect.pyo"
    "/srv/clusterfs/sdr/gnuradio/gr-customModule/build/python/customModule/escalar_flotante.pyo"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/srv/clusterfs/sdr/gnuradio/gr-customModule/build/python/customModule/bindings/cmake_install.cmake")

endif()

