module Arduino {
    @ I2C Driver for Arduino
    passive component I2cDriver {

        guarded input port write: Drv.I2c

        guarded input port read: Drv.I2c

    }
}
