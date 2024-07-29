module Arduino {
    @ I2C node driver for Arduino
    passive component I2cNodeDriver {

        output port write: Drv.I2c

        output port read: Drv.I2c
    }
}
