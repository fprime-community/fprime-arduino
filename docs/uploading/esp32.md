# ESP32 Dev Module

Hold down the `BOOT` button on the ESP32. Don't let go. Then run the commands below:

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

Once you see that data is being written (example shown below), you can let go of the button.

```
Writing at 0x00010000... (10 %)
Writing at 0x0001bbae... (20 %)
Writing at 0x0002425b... (30 %)
Writing at 0x000298e1... (40 %)
Writing at 0x0002eb67... (50 %)
Writing at 0x00033f5b... (60 %)
Writing at 0x0003ca7a... (70 %)
Writing at 0x000465db... (80 %)
Writing at 0x0004bc47... (90 %)
Writing at 0x00051160... (100 %)
```
