# STM32 Chips

These steps were tested and successfully uploaded for the following boards:
- NUCLEO-H723ZG
- NUCLEO-F401RE


```sh
# Linux
sh ~/.arduino15/packages/STMicroelectronics/tools/STM32Tools/2.3.0/stm32CubeProg.sh -i swd -f <YOUR_DEPLOYMENT> -c /dev/ttyACM0

# MacOS
sh ~/Library/Arduino15/packages/STMicroelectronics/tools/STM32Tools/2.3.0/stm32CubeProg.sh -i swd -f <YOUR_DEPLOYMENT> -c /dev/cu.usbmodem141203
```
> Change `<YOUR_DEPLOYMENT>` to the name of your F Prime deployment.
> 
> Change `/dev/ttyACM0` (`/dev/cu.usbmodem141203` for MacOS) to the correct serial device connected to the device.
