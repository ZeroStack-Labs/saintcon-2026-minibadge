# Firmware Information

While the code shipping with the kits is a .ino file, you'll more than likely quickly notice it's essentially C++. The good news is if you want to change what the LEDs do on this minibadge, it's fairly simple with a UPDI programmer like the [Adafruit Friend](https://www.digikey.com/en/products/detail/adafruit-industries-llc/5879/22596413) and 3 jumper wires or a similar setup.

## TP1

If you're looking at your kit (if you received one from me at SAINTCON 2026) or just browsing the KiCAD files or renders in this repo, you more than likely noticed a large touchpad on the PCB right above where the ATtiny402 MCU sits. That is TP1, and it connects to pin 6 on the 402, and allows for UPDI (re)programming. All you need to do is adjust/rewrite the code in Arduino IDE, set the board to the ATtiny series that contains the 402 chip, target specifically the 402 chip, connect power and ground, and a touch point of some kind (male end of a jumper wire, pogopin wired to UPDI, etc.) to the TP1 pad, and select upload using programmer from the menu options on the IDE. Make sure to hold that probe in place until the programming is completed! After that you should be able to see your new code in effect on the badge!

## Packaged Firmware

The chip you'll receive in the package is flashed with the code in this repo titled [zeroStack_minibadge_saintcon2026_breathing_leds.ino](/firmware/src/zeroStack_minibadge_saintcon2026_breathing_leds/zeroStack_minibadge_saintcon2026_breathing_leds.ino). However, depending on when you find/access this repo, there may be additional firmware options pre-written for you to try out.

But, keep in mind, this is my first ever PCB design let alone my first SAINTCON minibadge design, so it is very simple and beginner level, so there's not **too** much you can do with 2 green LED's (although I suppose if you're a HAM operator like myself, you could probably rig one to flash out your callsign in a visual representation of Morse Code). Hmm... I might just do that!

## Firmware Disclaimer

    This firmware and the associated hardware project were developed as a
    hands-on learning project with the assistance of AI tools, specifically
    ChatGPT. AI was used to help explain concepts, review design decisions,
    troubleshoot issues, and assist with code development while the project
    was being built and tested.

    This project is provided for educational and experimental purposes.
    Although reasonable effort has been made to test and validate the design,
    neither the firmware nor the hardware is guaranteed to be free of errors
    or suitable for any particular application.

    The overall license included with the above-mentioned GitHub repo must
    be followed regarding both the overall project and including this
    specific code.  Please reach out to me with any questions, tips,
    tricks, etc.

    Build, modify, and use this project at your own risk.

    Build | Break | Learn | Repeat
