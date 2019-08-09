# Infineon's XMC Microcontroller Boards for Arduino

This repository integrates [Infineon's](https://www.infineon.com/) XMC microcontrollers into the [Arduino IDE](https://www.arduino.cc/en/main/software) and [PlatformIO IDE](https://platformio.org/platformio-ide?utm_source=github&utm_medium=xmc-for-arduino).

## Additional Information

Please visit also the Wiki for additional information, e.g. datasheets, pin out diagrams, etc.:

[XMC-for-Arduino Wiki](https://github.com/cherrywalter/LarixEDU_Arduino/wiki)

## Installation Instructions

### Prework for SEGGER J-Link

In order to use the Larix EDU V3 and program it, you need [SEGGER J-Link](https://www.segger.com/downloads/jlink) installed on your PC. Please follow this link [SEGGER J-Link](https://www.segger.com/downloads/jlink) and install the J-Link Software and Documentation Pack for your respective operating system (OS).
If you have already installed '[DAVE™ - Development Platform for XMC™ Microcontrollers](https://infineoncommunity.com/dave-download_ID645)', you might skip this step as you should have the respective drivers on your system.

![J-Link](https://github.com/cherrywalter/LarixEDU_Arduino/wiki/pictures/implementation/J-Link_Packages.png)

### Integration in Arduino IDE

![Preferences](https://github.com/cherrywalter/LarixEDU_Arduino/wiki/pictures/implementation/Preferences.png)

Paste the following URL into the 'Additional Boards Manager URLs' input field under **File** > **Preferences** to add Infineon's microcontroller boards to the Arduino IDE.

https://github.com/cherrywalter/LarixEDU_Arduino/releases/download/current/package_infineon_index.json

Nicer to copy (no clickable link):

```
https://github.com/cherrywalter/LarixEDU_Arduino/releases/download/current/package_infineon_index.json
```

![Adding a Board JSON](https://github.com/cherrywalter/LarixEDU_Arduino/wiki/pictures/implementation/Preferences_JSON.png)

To install the boards, please go now to **Tools** > **Board** > **Boards Manager...** and search for XMC. You will see options to install the board files for the microcontrollers. Click "Install" to add the boards to your Arduino IDE. Beware that it is the version with Larix EDU V3 expansion.

![XMC board manager](https://github.com/cherrywalter/LarixEDU_Arduino/wiki/pictures/implementation/board_manager.PNG)

In the boards list **Tools** > **Board**, you will now find the XMC microcontroller boards XMC2Go, XMC1100 Boot Kit, XMC4700 Relax Kit and most important XMC4700 Larix EDU V3.

![Board List](https://github.com/cherrywalter/LarixEDU_Arduino/wiki/pictures/implementation/Board_List.PNG)

**IMPORTANT** Use the Debug USB port to flash the Larix EDU V3. The other port does not work.

### Different Notes

* **Note: This will only work for Arduino IDE >=1.5**
* **Note: Refer also to the LICENSE.md/txt file of the repositories for further information**
