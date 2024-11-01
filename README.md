# NXP Application Code Hub
[<img src="https://mcuxpresso.nxp.com/static/icon/nxp-logo-color.svg" width="100"/>](https://www.nxp.com)

## AN13953 Integrating NFC Reader Library in a KW4x Bluetooth Low Energy Application
This document gives instructions on how to create a Bluetooth Low Energy project for the EVK-KW45 development board and MCUXpresso IDE, and how to integrate NFC Reader Library

Please refer to AN13953 for complete instructions on how to use this software: [AN13953](https://docs.nxp.com/bundle/AN13953/page/topics/introduction.html).


#### Boards: x-KW45B41Z-EVK, CLRC663,PN5180,NCF3320 dev boards
#### Categories: Bluetooth LE, NFC Reader library
#### Peripherals: SPI, UART, GPIO, TIMER
#### Toolchains: MCUXpresso IDE


## Table of Contents
1. [Software](#step1)
2. [Hardware](#step2)
3. [Setup](#step3)
4. [Results](#step4)
5. [FAQs](#step5) 
6. [Support](#step6)
7. [Release Notes](#step7)

## 1. Software<a name="step1"></a>

The software for this Application Note is delivered in raw source files based on MCUXpresso IDE project.

- MCUXpresso IDE 11.7.0 or Later


## 2. Hardware<a name="step2"></a>

- KW45B41Z-EVK board as host MCU, used to load and run the Bluetooth Low Energy Stack and NFC application logic [KW45B41Z-EVK](https://www.nxp.com/design/design-center/software/development-software/mcuxpresso-software-and-tools-/kw45b41z-evaluation-kit-with-bluetooth-low-energy:KW45B41Z-EVK)
- NCF3320 Antenna v1.0 board as an NFC transceiver (With minor changes other NFC tranceiver (CLRC663,PN5180) can be supported)
- Wires for SPI communication
- Micro USB Cable
- Personal computer

Details on the connection between KW45B41Z-EVK and NFC reader board are listed here: 
[Hardware setup and configuration](https://docs.nxp.com/bundle/AN13953/page/topics/hardware_setup.html)

## 3. Setup<a name="step3"></a>
Use the following steps to get the environment set up.

This example assumes this repo is cloned into the "C:\work\" folder.

### 3.1 Step 1 Setting up the development environment (SDK download, workspace)
Use these [Details for setting up the environment](https://docs.nxp.com/bundle/AN13953/page/topics/setting_up_the_development_environment.html).

### 3.2 Step 2 Flashing NBU
Information regarding flashing NBU can be found in section 2.4 and 3.3 of the Getting Started page of [KW45B41Z-EVK](https://www.nxp.com/document/guide/getting-started-with-the-kw45b41z-evaluation-kit:GS-KW45B41ZEVK)
(NBU is located into the: C:\work\an-kw4x-bluetooth-le-nfc-integration\kw45b41zevk_w_uart_ncf3320_basic_discovery\source -> kw45b41_nbu_ble_hosted_a1.sb3)

### 3.3 Step 3 Download & install NFC Reader library v5.22.01
Download the NFC reader library [K82 NFC Reader Library package - PN7462AUPspPackageFull-v05_22_01](https://www.nxp.com/design/design-center/development-boards-and-designs/nfc-reader-library-software-support-for-nfc-frontend-solutions:NFC-READER-LIBRARY) and install it into the "C:\work\" folder.

### 3.4 Step 4 Integrate the NFC reader library
The current NFC Reader Library v5.22.01 does not support Kinetis KW4x MCU. 

To add the support, apply the patches as below:
```
C:\work\an-kw4x-bluetooth-le-nfc-integration\nfc_patch>nfc_patch.bat "C:\work\PN7462AUPspPackageFull-v05_22_01\PN7462AU Software\PN7462AU-FW_v05.22.01_Full" "C:\work\an-kw4x-bluetooth-le-nfc-integration" 
```

## 4. Results<a name="step4"></a>
Details on how to create the Bluetooth LE connection and get information from the NFC reader are listed here: [Running the demo](https://docs.nxp.com/bundle/AN13953/page/topics/running_the_demo.html)


## 5. FAQs<a name="step5"></a>
No FAQs have been identified for this project

## 6. Support<a name="step6"></a>

The details for this demo are all recorded in the application note: [AN13953](https://docs.nxp.com/bundle/AN13953/page/topics/introduction.html).

#### Project Metadata
<!----- Boards ----->
[![Board badge](https://img.shields.io/badge/Board-KW45B41Z&ndash;EVK-blue)](https://github.com/search?q=org%3Anxp-appcodehub+KW45B41Z-EVK+in%3Areadme&type=Repositories) [![Board badge](https://img.shields.io/badge/Board-K32W148&ndash;EVK-blue)](https://github.com/search?q=org%3Anxp-appcodehub+K32W148-EVK+in%3Areadme&type=Repositories)

<!----- Categories ----->
[![Category badge](https://img.shields.io/badge/Category-WIRELESS%20CONNECTIVITY-yellowgreen)](https://github.com/search?q=org%3Anxp-appcodehub+wireless_connectivity+in%3Areadme&type=Repositories)

<!----- Peripherals ----->
[![Peripheral badge](https://img.shields.io/badge/Peripheral-UART-yellow)](https://github.com/search?q=org%3Anxp-appcodehub+uart+in%3Areadme&type=Repositories) [![Peripheral badge](https://img.shields.io/badge/Peripheral-GPIO-yellow)](https://github.com/search?q=org%3Anxp-appcodehub+gpio+in%3Areadme&type=Repositories) [![Peripheral badge](https://img.shields.io/badge/Peripheral-SPI-yellow)](https://github.com/search?q=org%3Anxp-appcodehub+spi+in%3Areadme&type=Repositories) [![Peripheral badge](https://img.shields.io/badge/Peripheral-TIMER-yellow)](https://github.com/search?q=org%3Anxp-appcodehub+timer+in%3Areadme&type=Repositories)

<!----- Toolchains ----->
[![Toolchain badge](https://img.shields.io/badge/Toolchain-MCUXPRESSO%20IDE-orange)](https://github.com/search?q=org%3Anxp-appcodehub+mcux+in%3Areadme&type=Repositories)

Questions regarding the content/correctness of this example can be entered as Issues within this GitHub repository.

>**Warning**: For more general technical questions regarding NXP Microcontrollers and the difference in expected funcionality, enter your questions on the [NXP Community Forum](https://community.nxp.com/)

[![Follow us on Youtube](https://img.shields.io/badge/Youtube-Follow%20us%20on%20Youtube-red.svg)](https://www.youtube.com/@NXP_Semiconductors)
[![Follow us on LinkedIn](https://img.shields.io/badge/LinkedIn-Follow%20us%20on%20LinkedIn-blue.svg)](https://www.linkedin.com/company/nxp-semiconductors)
[![Follow us on Facebook](https://img.shields.io/badge/Facebook-Follow%20us%20on%20Facebook-blue.svg)](https://www.facebook.com/nxpsemi/)
[![Follow us on Twitter](https://img.shields.io/badge/Twitter-Follow%20us%20on%20Twitter-white.svg)](https://twitter.com/NXP)

## 7. Release Notes<a name="step7"></a>
| Version | Description / Update                           | Date                        |
|:-------:|------------------------------------------------|----------------------------:|
| 1.0     | Initial release on Application Code HUb        | September 17sup>th</sup> 2024 |

