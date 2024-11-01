# Feather ESP32 V2

```sh
chmod 0777 /dev/ttyACM0

# Linux
python3 ~/.arduino15/packages/esp32/tools/esptool_py/4.5.1/esptool.py --chip esp32 --port /dev/ttyACM0 --baud 921600  --before default_reset --after hard_reset write_flash -z --flash_mode keep --flash_freq keep --flash_size keep 0x1000 build-fprime-automatic-featherESP32/arduino-cli-sketch/tmpyi_eb6ss.ino.bootloader.bin 0x8000 build-fprime-automatic-featherESP32/arduino-cli-sketch/tmpyi_eb6ss.ino.partitions.bin 0xe000 ~/.arduino15/packages/esp32/hardware/esp32/2.0.9/tools/partitions/boot_app0.bin 0x10000 build-artifacts/featherESP32/<YOUR_DEPLOYMENT>/bin/<YOUR_DEPLOYMENT>.elf.bin

# MacOS
python3 ~/Library/Arduino15/packages/esp32/tools/esptool_py/4.5.1/esptool.py --chip esp32 --port /dev/tty.usbmodem12345 --baud 921600  --before default_reset --after hard_reset write_flash -z --flash_mode keep --flash_freq keep --flash_size keep 0x1000 build-fprime-automatic-featherESP32/arduino-cli-sketch/tmpyi_eb6ss.ino.bootloader.bin 0x8000 build-fprime-automatic-featherESP32/arduino-cli-sketch/tmpyi_eb6ss.ino.partitions.bin 0xe000 ~/Library/Arduino15/packages/esp32/hardware/esp32/2.0.9/tools/partitions/boot_app0.bin 0x10000 build-artifacts/featherESP32/<YOUR_DEPLOYMENT>/bin/<YOUR_DEPLOYMENT>.elf.bin
```
> Change `<YOUR_DEPLOYMENT>` to the name of your F Prime deployment.
> 
> Change `/dev/ttyACM0` (`/dev/tty.usbmodem12345` for MacOS) to the correct serial device connected to the ESP32.
>
> Change `tmpyi_eb6ss` to the actual temporary file name located in `build-fprime-automatic-featherESP32/arduino-cli-sketch`
