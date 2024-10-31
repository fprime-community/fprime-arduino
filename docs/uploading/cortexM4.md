# ARM Cortex-M4 Chips

These steps were tested and successfully uploaded for the following boards:
- Adafruit Feather M4
- Adafruit Metro M4 Grand Central

Double press on the reset button on the Feather to set it to programming mode. Then run the following commands below.

```sh
# Linux
~/.arduino15/packages/adafruit/tools/bossac/1.8.0-48-gb176eee/bossac -i -d --port=ttyACM0 -U -i --offset=0x4000 -w -v ./build-artifacts/<YOUR_TOOLCHAIN>/<YOUR_DEPLOYMENT>/bin/<YOUR_DEPLOYMENT>.bin -R

# MacOS
~/Library/Arduino15/packages/adafruit/tools/bossac/1.8.0-48-gb176eee/bossac -i -d --port=tty.usbmodem12345 -U -i --offset=0x4000 -w -v ./build-artifacts/<YOUR_TOOLCHAIN>/<YOUR_DEPLOYMENT>/bin/<YOUR_DEPLOYMENT>.bin -R
```
> Change `<YOUR_DEPLOYMENT>` to the name of your F Prime deployment.
> 
> Change `/dev/ttyACM0` (`/dev/tty.usbmodem12345` for MacOS) to the correct serial device connected to the device.
