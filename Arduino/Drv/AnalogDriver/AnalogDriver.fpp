module Drv {

    port AnalogWrite(val: U8) -> Fw.Success
    
    port AnalogRead(ref val: U16 ) -> Fw.Success

}

module Arduino {
    @ Analog Driver for Arduino boards
    passive component AnalogDriver {

        @ Set analog value from 0-255
        sync input port setAnalog: Drv.AnalogWrite

        @ Read analog value between 0-4095
        sync input port readAnalog: Drv.AnalogRead

    }
}