// ======================================================================
// \title  GpioDriverImpl.cpp
// \author tcanham
// \brief  cpp file for GpioDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include <Arduino/Drv/GpioDriver/GpioDriver.hpp>
#include <FpConfig.hpp>

namespace Arduino {

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

bool GpioDriver ::open(NATIVE_INT_TYPE gpio, GpioDirection direction) {
    m_pin = gpio;
    return true;
}

void GpioDriver ::gpioRead_handler(const NATIVE_INT_TYPE portNum, Fw::Logic& state) {
    state = Fw::Logic::LOW;
}

void GpioDriver ::gpioWrite_handler(const NATIVE_INT_TYPE portNum, const Fw::Logic& state) {
}
}
