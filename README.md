# Arduino robot car

This project is based on the "2wd arduino smart car kit" or "smart robot car kit" kits that can be bought for around $20 on ebay. For assembly of the body, search for one of those phrases and there are various videos and pictures that can be used as a reference.

The modified schematic provided [here](robocar_schematic.pdf) gives a very cheap way to put 2 rechargeable 18650 lipo batteries on the car for much better performance than AA batteries.

A list of parts is available [here](partslist.md).

General instructions:

See the [schematics](robocar_schematic.pdf) for a diagram of how to wire the batteries, chargers, and motors on the car. Hopefully all the pins on your parts will be labeled and match the schematic. On the DPDT switch (see [this](https://learn.sparkfun.com/tutorials/switch-basics/poles-and-throws-open-and-closed) for switch explaination), the pins would be numbered like this when looking at it from below:

| 1  | 4 |
| --- | --- |
| 2  | 5  |
| 3 | 6  |

Or any mirrored version of that. I recommend numbering each pin on the switch to keep track of them.

The bluetooth module tx and rx pins should be wired to the arduino's rx and tx pins, respectively. Also connect Vcc (or Vin or 5v or 3v something) and gnd to the arduino's 5v (or 3v if the module says that) and ground. Ignore the last 2 pins if the bluetooth module has them.

## Programming the car

The cars are controlled by Arduinos programmed in C/C++. Check out the [Arduino getting started page](https://www.arduino.cc/en/Guide/HomePage) to download the Arduino IDE and get started.

Code examples for programming the car can be found [here]("./example sketches"). They can be opened and uploaded the the car's Arduino with the Arduino IDE. Simple example programs are also included in the Arduino IDE under File>Examples. Instructions for using each sketch can be found either in that sketch as comments or it's readme.md.

Read through the car_bluetooth_control_1 example sketch because it has excellent comments explaining how everything works.