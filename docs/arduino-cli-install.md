# Arduino CLI Installation Guide

This guide will walk through the installation of the `arduino-cli` and `arduino-cli-cmake-wraper` components used to bridge F Prime and the Arduino build system. This assumes a virtual environment has been setup for your project.

> Activate the project virtual environment now.

## Install arduino-cli
```shell
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=$VIRTUAL_ENV/bin sh
```

This command downloads `arduino-cli` and installs the binary into the existing (and activated) virtual environment.

## Install arduino-cli-wrapper
```shell
pip install arduino-cli-cmake-wrapper
```

## Setup arduino-cli for select Arduino boards

Initialize the arduino-cli configuration file.
```shell
arduino-cli config init
```

Below are board manager URLs for select Arduino boards. You are not required to add all of these boards, but you are free to do so.
```shell
arduino-cli config add board_manager.additional_urls https://www.pjrc.com/teensy/package_teensy_index.json
arduino-cli config add board_manager.additional_urls https://adafruit.github.io/arduino-board-index/package_adafruit_index.json
arduino-cli config add board_manager.additional_urls https://espressif.github.io/arduino-esp32/package_esp32_index.json
arduino-cli config add board_manager.additional_urls https://arduino.esp8266.com/stable/package_esp8266com_index.json
arduino-cli config add board_manager.additional_urls https://mcudude.github.io/MegaCore/package_MCUdude_MegaCore_index.json
arduino-cli config add board_manager.additional_urls https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
arduino-cli config add board_manager.additional_urls https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json
```

Install the new board packages. Only install the ones you have added to your board manager in the previous step.
```shell
arduino-cli core update-index
arduino-cli core install arduino:avr
arduino-cli core install teensy:avr
arduino-cli core install adafruit:samd
arduino-cli core install adafruit:nrf52
arduino-cli core install esp32:esp32@2.0.9
arduino-cli core install esp8266:esp8266
arduino-cli core install MegaCore:avr
arduino-cli core install rp2040:rp2040
arduino-cli core install STMicroelectronics:stm32
```

> ESP32: As of 10/27/2024, versions newer than `esp32:esp32@2.0.9` will not work.

If you are building the Adafruit NRF52 boards and are on Linux, you must also install:
```sh
pip install adafruit-nrfutil
```

[The following list](./board-list.md) shows the tested boards successfully running an F Prime deployment.

## Library Dependencies
Required Dependencies:
```shell
arduino-cli lib install Time
```

If you will be using the `TcpClient` component, install:
```shell
arduino-cli lib install WiFi
```

## Adding udev rules (Linux Only)
Add udev rules. Download/save the `.rules` files located [here](https://github.com/fprime-community/fprime-arduino/tree/main/docs/rules) for your selected board(s) into `/etc/udev/rules.d/`.


### Next Step: [Building and Running the Base Deployment on Hardware](./run-base-deployment.md)