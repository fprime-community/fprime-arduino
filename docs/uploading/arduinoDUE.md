# Arduino DUE

```sh
# Linux
~/.arduino15/packages/arduino/tools/bossac/1.6.1-arduino/bossac -i -d --port=ttyUSB0 -U false -e -w -b build-artifacts/arduinodue/<YOUR_DEPLOYMENT>/bin/<YOUR_DEPLOYMENT>.elf.bin -R

# MacOS
~/Library/Arduino15/packages/arduino/tools/bossac/1.6.1-arduino/bossac -i -d --port=tty.usbmodem12345 -U false -e -w -b build-artifacts/arduinodue/<YOUR_DEPLOYMENT>/bin/<YOUR_DEPLOYMENT>.elf.bin -R
```

> Change `<YOUR_DEPLOYMENT>` to the name of your F Prime deployment.
> 
> Change `/dev/ttyUSB0` (`/dev/tty.usbmodem12345` for MacOS) to the correct serial device connected to the device.