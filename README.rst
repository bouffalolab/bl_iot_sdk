BL602 SDK (Pine64 version)
==========================

Join us on `Discord <https://discord.gg/89VWQVH>`_, `Telegram <https://t.me/joinchat/Kmi2S0nOsT240emHk-aO6g>`_, `Matrix <https://matrix.to/#/#pine64-nutcracker:matrix.org>`_

This repository contains the Pine64 fork of Bouffalo Lab's SDK for their BL602
Wi-Fi/BLE Combo RISC-V SoC. The upstream documentation lives in ``docs/html``.

This repository is the central focus of Pine64's
`Nutcracker Challenge <https://www.pine64.org/2020/10/28/nutcracker-challenge-blob-free-wifi-ble/>`_.

Quick Start
-----------
In order to build one of the sample apps, you need to set a few environment
variables::

    export BL60X_SDK_PATH=/path/to/this/repo
    export CONFIG_CHIP_NAME=bl602

Then go to the sample directory of interest and call `make`, for example::

    cd customer_app/bl602_boot2
    make

Call ::

    make CONFIG_TOOLPREFIX=riscv64-linux-gnu-

for bypassing the bundled cross-compiler and using your distribution's own
cross-compiler.

There is a linker script (written in python) at `image_conf/flash_build.py`.
To run this, you need to specify the application and the target, for example::

    python3 flash_build.py bl602_boot2 bl602

Hardware
--------
BL602 is a 32-bit RISC-V based combo chipset supporting Wi-Fi and BLE (Bluetooth
Low Energy). The chip is made by `Nanjing-based Bouffalo Lab <https://www.bouffalolab.com/bl602>`_
for ultra-low-power applications. In terms of price range and feature set, the
chip is competing against `Espressif ESP8266 <https://www.espressif.com/en/products/socs/esp8266>`_

- `BL602/604 Datasheet <docs/BL602_BL604_DS_Datasheet.pdf>`_
  (34 pages): Includes pinout, memory map, and general peripheral descriptions
  but no detailed functional specification or register listings. Sipeed, a board
  vendor that plans to use the BL602, `claims <https://twitter.com/SipeedIO/status/1321658609990725633>`_
  that full register documentation will be available sometime in November 2020.
- `soc602_reg.svd <components/bl602/bl602_std/bl602_std/Device/Bouffalo/BL602/Peripherals/soc602_reg.svd>`_:
  Contains a seemingly-complete register listing, with names but no descriptions,
  for the BL602.
- `Hardware Notes <docs/hardware_notes.md>`_: Additional information gathered
  from this repository and elsewhere on the internet.

Comparison with ESP8266
-----------------------
+-------------------+-----------------------------+----------------------------------+
|                   | Bouffalo Lab BL602          | Espressif ESP8266                |
+===================+=============================+==================================+
| Architecture      | 32-bit RISC-V               | 32-bit Xtensa                    |
|                   |                             |                                  |
|                   | @192MHz (dynamic @1-192MHz) | @80MHz (and 160MHz)              |
|                   |                             |                                  |
|                   | L1 cache                    |                                  |
|                   |                             |                                  |
|                   | FPU                         |                                  |
+-------------------+-----------------------------+----------------------------------+
| Memory            | 276KB SRAM                  | 32 KiB instruction RAM           |
|                   |                             |                                  |
|                   | 128KB ROM                   | 32 KiB instruction cache RAM     |
|                   |                             |                                  |
|                   | 1 Kb eFuse                  | 80 KiB user-data RAM             |
|                   |                             |                                  |
|                   | optional embdedded flash    | 16 KiB ETS system-data RAM       |
|                   |                             |                                  |
|                   |                             |                                  |
|                   | XIP QSPI flash support      | No programmable ROM              |
|                   |                             |                                  |
|                   |                             | QSPI flash support               |
|                   |                             | (up to 16 MB)                    |
+-------------------+-----------------------------+----------------------------------+
| Wi-Fi             | 802.11 b/g/n @2.4GHz        | 802.11 b/g/n @2.4GHz             |
|                   |                             |                                  |
|                   | WPS/WEP/WPA/WPA2/WPA3       | WEP/WPA/WPA2                     |
+-------------------+-----------------------------+----------------------------------+
| Bluetooth         | LE 5.0                      | NONE                             |
+-------------------+-----------------------------+----------------------------------+
| GPIO              | x16                         | x16                              |
+-------------------+-----------------------------+----------------------------------+
| SDIO              | x1 2.0 slave                | x1 v2.0 slave                    |
+-------------------+-----------------------------+----------------------------------+
| SPI               | x1                          | x2                               |
+-------------------+-----------------------------+----------------------------------+
| UART              | x2                          | x1.5                             |
|                   |                             | (One Tx only)                    |
+-------------------+-----------------------------+----------------------------------+
| I2C               | x1                          | x1 (software implemented)        |
+-------------------+-----------------------------+----------------------------------+
| I2S               | NONE                        | x1 (with DMA)                    |
+-------------------+-----------------------------+----------------------------------+
| PWM channels      | x5                          | x4                               |
+-------------------+-----------------------------+----------------------------------+
| ADC               | 12-bit                      | 10-bit (SAR)                     |
+-------------------+-----------------------------+----------------------------------+
| DAC               | 10-bit                      | NONE                             |
+-------------------+-----------------------------+----------------------------------+
| Analog Comparator | x2                          | NONE                             |
+-------------------+-----------------------------+----------------------------------+
| DMA               | x4                          | with I2S                         |
+-------------------+-----------------------------+----------------------------------+
| Timer             | RTC (up to 1 year)          | x1 hardware                      |
|                   |                             |                                  |
|                   | x2 32-bit general-purpose   | x1 software                      |
|                   |                             |                                  |
|                   |                             | (no interrupt gen. on sw. timer) |
+-------------------+-----------------------------+----------------------------------+
| IR Remote Control | x1                          | x1                               |
+-------------------+-----------------------------+----------------------------------+
| Debug             | JTAG support                | ?                                |
+-------------------+-----------------------------+----------------------------------+
