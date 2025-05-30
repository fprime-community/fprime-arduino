module Arduino {
    @ TCP Server for Arduino
    passive component TcpServer {

        include "../../../../fprime/Drv/Interfaces/ByteStreamDriverInterface.fppi"

        @ Allocation for received data
        output port allocate: Fw.BufferGet

        @ Deallocation of allocated buffers
        output port deallocate: Fw.BufferSend

    }
}
