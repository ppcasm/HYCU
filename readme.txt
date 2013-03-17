HyperScan Cable Uploader

This tool is for quickly testing homebrew applications for the Mattel HyperScan console.

Intro:

This tool constists of 3 parts in order to make the testing platform more transparent. The 
3 parts are as listed:

1: PC Side
2: MCU Side
3: HyperScan Side

The idea here is that the PC side, and the HyperScan side interfacing remains the same in that
it sends out data through serial (usually USB serial) from the PC side to the MCU, and the 
HyperScan side accepts a translated version of this data. This means that all that essentially
has to be done to "port" this environment to another device is to write the code for the MCU
to do the translation, and the rest of the environment should work as normal.

The job of the MCU code is to act as the middle man in order to translate the serial data 
coming in, into a very simple sync serial interface that works over the controller port.

At the last of this chain is the HyperScan side. The job of the hyperscan side is to take this
sync serial data coming in over the controller port and translate it into a working machine 
code representation that gets saved to HyperScans RAM as a working program. 


Instructions:

First, you have to build a cable that connects from your MCU into the HyperScan controller port.
The controller port appears to use standard a standard PS/2 male connector cable, but you can
just as easily use an existing HyperScan controller cable if you have one on hand.

The wiring diagrams I will provide include coloring, numbering, and signaling. The coloring is 
for the HyperScan controller wires, while the numbering generally is used in the case where you
decide to build the cable out of a standard PS/2 cable.

This should keep one from having to modify and/or open their system in any way so as to not risk
messing up a "rare" system that's not being produced anymore. There should also be minimal to no
soldering required depending on how you plan to wire your controller wires to your MCU. This also
makes it less of a hassel for people who don't like messing with hardware but would rather write
software.

After you have your cable built, you need to compile the PC side of the code, your MCU code, and 
the HyperScan side. The HyperScan side ends up as a .bin in your Debug folder in the source tree,
at which point you'll need to rename it to HYPER.EXE and burn it to a data cd.

After this, load your MCU code into your MCU. At this point all the wires should be wired into the 
MCU in whatever fashion the code is configured for. At this point you can start up the PC side of
the loader, and the usage goes as follows:

<HYCU.exe> <COM_PORT> <BAUD> <UPLOAD_ADDRESS> <FILE_NAME>

At this point, you should generally see some indication lights on the MCU letting you know that the
code is uploading, and the HyperScan should give you a proper upload address, and size, and the status
indicator should read "DONE" when it's finished.

Notes on porting MCU code to other platforms:

When writing the code for the MCU, I've tried to keep the wiring so that it matches up with the MCU
I2C port on boards that happen to have one. The controller interface appears to use I2C, and I plan
on adding I2C support later on, and so this would allow that upgrade to happen transparently through
software. An example of this is that pin 20 on Arduino is also shared with the "SDA" signal. It's 
being used as a GPIO on pin 20 for now, but later on with the update it could then become the I2C SDA
signaling. 
 

Controller Male Connector Pinout:

     3   4
    2  I  5  
     1 I 6

# : Color  : Signal

1 : brown  : GND
2 : yellow : DATA
3 : grey   : CLK
4 : green  : ENABLE
5 : blue   : RESET
6 : red    : VCC 3.3v

