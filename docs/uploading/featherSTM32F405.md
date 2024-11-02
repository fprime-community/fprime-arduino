# Adafruit Feather STM32F405

Connect the `3.3V` and `B0` pins on your board.

![Connection Diagram](https://cdn-learn.adafruit.com/assets/assets/000/083/669/medium640/feather_boards_image.png?1573006270)

```sh
# Windows (WSL)
 ~\AppData\Local\Arduino15\packages\STMicroelectronics\tools\STM32Tools\2.2.3\win\busybox.exe sh ~\AppData\Local\Arduino15\packages\STMicroelectronics\tools\STM32Tools\2.2.3\stm32CubeProg.sh -i dfu -f .\LedBlinker.elf.bin -o 0x0 -v 0x0483 -p 0xdf11

# Linux / MacOS
~/.arduino15/packages/STMicroelectronics/tools/STM32Tools/2.2.3/linux/dfu-util -a 0 --dfuse-address 0x08000000 -D build-artifacts/featherSTM32F405/LedBlinker/bin/LedBlinker.elf.bin
```
