// ======================================================================
// \title  SerialDriverImpl.cpp
// \author lestarch
// \brief  cpp file for SerialDriver component implementation class
// ======================================================================

#include <Arduino/Drv/SerialDriver/SerialDriver.hpp>
#include <FprimeArduino.hpp>
#include <Os/Log.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include "Fw/Types/Assert.hpp"
namespace Arduino
{

    void SerialDriver::configure(FwIndexType port_number, PlatformIntType baud)
    {
        switch (port_number)
        {
        case 0:
            m_port_pointer = reinterpret_cast<Stream *>(&Serial);
            Serial.begin(baud);
            break;
        case 1:
            m_port_pointer = reinterpret_cast<Stream *>(&Serial1);
            Serial1.begin(baud);
            break;
        case 2:
            m_port_pointer = reinterpret_cast<Stream *>(&Serial2);
            Serial2.begin(baud);
            break;
        case 3:
            m_port_pointer = reinterpret_cast<Stream *>(&Serial3);
            Serial3.begin(baud);
            break;
        case 4:
            m_port_pointer = reinterpret_cast<Stream *>(&Serial4);
            Serial4.begin(baud);
            break;
        case 5:
            m_port_pointer = reinterpret_cast<Stream *>(&Serial5);
            Serial5.begin(baud);
            break;
        case 6:
            m_port_pointer = reinterpret_cast<Stream *>(&Serial6);
            Serial6.begin(baud);
            break;
        case 7:
            m_port_pointer = reinterpret_cast<Stream *>(&Serial7);
            Serial7.begin(baud);
            break;
        default:
            FW_ASSERT(0, port_number); // invalid port number
        }
        this->ready_out(0);
    }

    // ----------------------------------------------------------------------
    // Handler implementations for user-defined typed input ports
    // ----------------------------------------------------------------------

    void SerialDriver ::write_data(Fw::Buffer &fwBuffer)
    {
        FW_ASSERT(m_port_pointer != 0);
        reinterpret_cast<Stream *>(m_port_pointer)
            ->write(reinterpret_cast<U8 *>(fwBuffer.getData()), fwBuffer.getSize());
    }

    void SerialDriver ::read_data(Fw::Buffer &fwBuffer)
    {
        Stream *serial_ptr = reinterpret_cast<Stream *>(m_port_pointer);
        int byte = 0;
        NATIVE_UINT_TYPE count = 0;
        U8 *raw_data = reinterpret_cast<U8 *>(fwBuffer.getData());
        while ((serial_ptr->available() > 0) && (count < fwBuffer.getSize()) && ((byte = serial_ptr->read()) != -1))
        {
            *(raw_data + count) = static_cast<U8>(byte);
            count++;
        }
        fwBuffer.setSize(count);
    }
} // namespace Arduino
