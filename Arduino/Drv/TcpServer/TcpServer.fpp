module Arduino {
    @ TCP Server for Arduino board with WiFi support
    passive component TcpServer {

        import ByteStreamDriver

        @ Allocation for received data
        output port allocate: Fw.BufferGet

        @ Deallocation of allocated buffers
        output port deallocate: Fw.BufferSend

        @ Polling for receiving data
        sync input port schedIn: Svc.Sched

    }
}
