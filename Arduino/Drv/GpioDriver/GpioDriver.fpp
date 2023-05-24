module Arduino {
  passive component GpioDriver {
    sync input port gpioWrite: Drv.GpioWrite
    sync input port gpioRead: Drv.GpioRead
  }
}
