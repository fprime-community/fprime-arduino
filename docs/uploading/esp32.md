# ESP32 Dev Module

```sh
chmod 0777 /dev/ttyACM0

# Linux
python3 ~/.arduino15/packages/esp32/tools/esptool_py/4.5.1/esptool.py --chip esp32 --port /dev/ttyUSB0 --baud 921600  --before default_reset --after hard_reset write_flash -e -z --flash_mode dio --flash_freq 80m --flash_size 4MB 0x1000 build-fprime-automatic-esp32/arduino-cli-sketch/tmp8lcl76bw.ino.bootloader.bin 0x8000 build-fprime-automatic-esp32/arduino-cli-sketch/tmp8lcl76bw.ino.partitions.bin 0xe000 ~/.arduino15/packages/esp32/hardware/esp32/2.0.9/tools/partitions/boot_app0.bin 0x10000 build-artifacts/esp32/<YOUR_DEPLOYMENT>/bin/<YOUR_DEPLOYMENT>.bin

# MacOS
python3 ~/Library/Arduino15/packages/esp32/tools/esptool_py/4.5.1/esptool.py --chip esp32 --port /dev/tty.usbmodem12345 --baud 921600  --before default_reset --after hard_reset write_flash -e -z --flash_mode dio --flash_freq 80m --flash_size 4MB 0x1000 build-fprime-automatic-esp32/arduino-cli-sketch/tmp8lcl76bw.ino.bootloader.bin 0x8000 build-fprime-automatic-esp32/arduino-cli-sketch/tmp8lcl76bw.ino.partitions.bin 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/2.0.9/tools/partitions/boot_app0.bin 0x10000 build-artifacts/esp32/<YOUR_DEPLOYMENT>/bin/<YOUR_DEPLOYMENT>.bin
```
> Change `<YOUR_DEPLOYMENT>` to the name of your F Prime deployment.
> 
> Change `/dev/ttyACM0` (`/dev/tty.usbmodem12345` for MacOS) to the correct serial device connected to the ESP32.
>
> Note: Change `tmp8lcl76bw` to the actual temporary file name located in `build-fprime-automatic-esp32/arduino-cli-sketch`
