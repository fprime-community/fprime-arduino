module Arduino {

  passive component StreamDriver {

    @ Polling for receiving data
    sync input port schedIn: Svc.Sched

    @ Allocation port used for allocating memory in the receive task
    output port allocate: Fw.BufferGet

    @ Deallocation of allocated buffers
    output port deallocate: Fw.BufferSend

    @ TODO: Update once interfaces are fully supported in fpp
    include "../../../../fprime/Drv/Interfaces/ByteStreamDriverInterface.fppi"
  }
}
