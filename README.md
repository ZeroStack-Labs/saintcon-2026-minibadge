<h1><span style="color:#A3FF12">ZeroStack Labs SAINTCON 2026 MiniBadge</span></h1>

A custom SAINTCON-compatible MiniBadge designed as a ZeroStack Labs hardware/firmware learning project.

This project combines PCB design, embedded firmware, 3D printing, mechanical design, and custom fabrication into a small badge intended for use with the SAINTCON MiniBadge ecosystem.

The finished design features an ATtiny402 microcontroller, two green LEDs, a custom two-color 3D-printed topper, and a dedicated UPDI programming/test jig.

> **Project status:** Prototype / active development  
> The PCB has been ordered and the 3D-printed topper design has reached a successful production prototype.

---

## Features

- SAINTCON MiniBadge-compatible footprint and pinout
- Custom 25.4 mm × 25.4 mm PCB
- ATtiny402 microcontroller
- Two individually controlled green LEDs
- UPDI programming test point
- Custom ZeroStack Labs silkscreen artwork
- Two-color 3D-printed topper
- Acid-green translucent logo/inlay
- Black structural backing layer
- M2 self-tapping mounting screws
- Custom 3D-printed programming jig
- Planned LED breathing / animation firmware

---

## Project Goals

This project started as a way to learn more about:

- KiCad PCB design
- Embedded microcontrollers
- UPDI programming
- Surface-mount soldering
- PCB fabrication
- Multi-color 3D printing
- Mechanical integration between a PCB and printed topper
- Firmware development for small embedded devices

The design files are being published so others can study the project, modify it, and create their own MiniBadge variations.

---

## Hardware

### Microcontroller

The badge uses a **Microchip ATtiny402-SSN** in an SOIC-8 package.

| ATtiny402 Pin | Function               |
| ------------- | ---------------------- |
| VCC           | +3.3 V                 |
| GND           | Ground                 |
| PA1           | LED 1                  |
| PA2           | LED 2                  |
| PA0 / UPDI    | Programming test point |

Unused pins are intentionally left unconnected.

### LEDs

Two green 1206 LEDs are driven through 220 ohm current-limiting resistors.

Approximate LED current:

```text
(3.3 V - 2.1 V) / 220 ohm ≈ 5.5 mA
```

### Decoupling

A 0.1 uF ceramic capacitor is placed close to the ATtiny402 VCC and GND pins.

---

## MiniBadge Interface

The PCB follows the open MiniBadge pinout and interface convention.

Relevant pins used by this design include:

| Pin | Function |
| --- | -------- |
| 1   | VBATT    |
| 2   | GND      |
| 7   | +3V3     |
| 8   | GND      |
| 9   | CLK      |
| 10  | NC       |
| 15  | +3V3     |
| 16  | GND      |

Only the required header positions are intended to be populated, while the PCB retains the complete 16-hole MiniBadge footprint.

> **Important:** VBATT and +3V3 are not connected together.

---

## PCB

The PCB was designed in **KiCad 10**.

### Board dimensions

- 25.4 mm × 25.4 mm
- Rounded square outline
- 2 mm corner radius
- Three 2.2 mm mounting holes

### Fabrication

The first production run was ordered through **OSH Park** using the **After Dark** process.

Fabrication outputs include:

- Front copper
- Back copper
- Front solder mask
- Back solder mask
- Front silkscreen
- Back silkscreen
- Edge cuts
- Plated through-hole drill file
- Non-plated through-hole drill file

---

## 3D-Printed Topper

The topper is designed as a two-color print consisting of:

1. A black structural body
2. A translucent green ZeroStack Labs artwork/inlay

The successful production prototype is:

**V10.1**

### Production files

```text
ZeroStack_Topper_FINAL_v10_1_BLACK_BODY.stl
ZeroStack_Topper_FINAL_v10_1_GREEN_INLAY.stl
```

### Printing workflow

The two STL files are imported into **Flash Studio**, assembled as separate objects, and assigned different filaments.

Recommended orientation:

- **Face down**
- **Mounting posts up**

Printing face-down allows the visible surface to inherit the PEI build plate texture while keeping layer lines on the hidden rear surface.

### Topper construction

- Total top plate thickness: 2.0 mm
- Solid black backing: 0.5 mm
- Green inlay depth: 1.5 mm
- Mounting post diameter: approximately 4.5 mm
- M2 self-tapping pilot hole: approximately 1.7 mm

The mounting posts use a reinforced/tapered base to improve print reliability.

---

## Programming Jig

A custom 3D-printed jig was created to simplify programming and testing.

The jig uses the MiniBadge header locations to position the PCB and provides access to the ATtiny402 UPDI test point.

The intended programming setup uses:

- MiniBadge +3V3
- MiniBadge GND
- One pogo pin contacting the UPDI test pad

An Arduino Uno R3 may be used as a UPDI programmer with suitable firmware/software.

Programming documentation will be added as the firmware workflow is finalized.

---

## Firmware

Firmware is planned for the ATtiny402 to control both LEDs.

Initial goals include:

- Smooth breathing animation
- Adjustable brightness
- Adjustable breathing speed
- Optional alternating LED phase
- Simple constants for easy customization

---

## Repository Structure

```text
saintcon-2026-minibadge/
├── README.md
├── LICENSE
├── hardware/
│   ├── pcb/
│   ├── gerbers/
│   └── bom/
├── mechanical/
│   ├── topper/
│   └── programming-jig/
├── firmware/
├── docs/
└── assets/
```

---

## Bill of Materials

| Qty / Badge        | Component           | Part                    |
| ------------------ | ------------------- | ----------------------- |
| 1                  | Microcontroller     | Microchip ATtiny402-SSN |
| 1                  | 0.1 uF capacitor    | KEMET C0805C104K8RACTU  |
| 2                  | 220 ohm resistor    | Yageo RC1206FR-07220RL  |
| 2                  | Green LED           | Kingbright APTL3216CGCK |
| 4 × 2-pin sections | 2.54 mm male header | Sullins PREC040SAAN-RC  |

Additional parts include mounting screws and the printed topper.

---

## Assembly Notes

Recommended assembly order:

1. Inspect the bare PCB.
2. Solder the ATtiny402.
3. Solder the 0.1 uF decoupling capacitor.
4. Solder the two 220 ohm resistors.
5. Solder the two LEDs.
6. Check for shorts between +3V3 and GND.
7. Program and test the ATtiny402.
8. Install the MiniBadge headers.
9. Attach the printed topper.
10. Perform final functional testing.

For a batch build, fully assemble and test **one badge first** before assembling the remainder.

---

## Credits

This project would not exist without the work of **Luke Jenkins and the contributors to the MiniBadge standard**.

The PCB interface and footprint used in this project are based on the open MiniBadge project:

**https://github.com/lukejenkins/minibadge**

The MiniBadge project provided the pinout, footprint convention, and reference material used as the foundation for this SAINTCON-compatible design.

Huge thanks to the original authors and contributors for making the standard and design resources publicly available.

---

## Disclaimer

This project was created as a learning project by a beginner in PCB and embedded hardware design.

While the design has been reviewed and tested to the best of my ability, it may contain mistakes, design limitations, or implementation issues.

**Use these files at your own risk.**

Before manufacturing, assembling, modifying, or powering the design, independently verify:

- Schematic connections
- PCB layout
- Component orientation
- Component ratings
- Power requirements
- Firmware behavior
- Mechanical clearances

ZeroStack Labs and the project author are not responsible for damage to hardware, components, tools, computers, programmers, host devices, or other equipment resulting from the use or modification of this project.

---

## License

This project is intended to be open source and is released under the **MIT License**, unless otherwise noted for third-party assets or referenced projects.

You are welcome to:

- Study the design
- Modify it
- Build your own version
- Create derivative projects
- Use the files as a learning resource

Please preserve any required third-party attribution where applicable.

---

## About ZeroStack Labs

**ZeroStack Labs** is a personal technology lab focused on learning, experimentation, cybersecurity, software development, hardware projects, 3D printing, and hands-on technical education.

This MiniBadge is one of the first hardware projects developed under the ZeroStack Labs name.

---

## Future Work

Planned additions include:

- ATtiny402 breathing LED firmware
- UPDI programming guide
- Assembly photos
- Soldering notes
- Final PCB photos
- Completed badge photos
- Programming jig documentation
- Alternate topper colors / special editions
- Video build series for the ZeroStack Labs YouTube channel
