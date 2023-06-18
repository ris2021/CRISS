<h1>CRISS CP/M Project</h1>

The first DIY full-featured computer supporting VGA, Mouse, Pronter, Ethernet, RTC, GPIO with CP/M OS and Z80 compatible instuction set! No kits and pre-assebled boards, DIP components only, clear design and standard Atmel AVR ATMEGA and ATTINY MCUs only!

<img src=criss_bw_draw.png>

CRISS is a 21st-century CP/M single-board computer based mainly on AVR microcontrollers. The CPU is a 20 MHz ATMEGA1284P, which imitates a 4 MHz Z80 through machine-code emulation. A pair of ATMEGA328s run the peripheral controller and a VGA output, so the CRISS can be used with modern monitors. Basically image is monochrome green-on-black, looking instantly familiar to users of Kaypro's, Osborne's and other contemporary CP/M machines.

Started from May 2023 color support was added by additional MCU ATTiny84, now CRISS CP/M supports VGA output with 8 text colors!

<img src=DSC_0246_HD.jpg width=70%>

Software is loaded through an SD card that holds floppy images. The CRISS can directly run programs written for the Kaypro II and Robotron 1715 computers, although other platforms can be supported as well with a software upgrade. 

Housed in a neat little case (13x10cm PCB size), the CRISS can communicate with standard PS/2 keyboards and serial printers. Even an Ethernet port is provided for those willing to experiment with network connectivity (a rare feature in the 1980s).

Amazing functionality for the DIY device: it is not a toy, it is REAL Computer, the SAFEST computer in the world and the sophisticated control platform for your projects!

<h2>Features:</h2>

<ul>
<li> OS: CP/M 2.2 = programming languages, text processors, games, business software, etc.
<li> Instructions: Z80 (Zilog), extended with MUL, DIV, and floating-point, control time 1us LD r,r ops
<li> Memory: 64Kb SRAM, 128 Kb EPROM
<li> Video: VGA (!), 8 colors, up to 25x80 chars, 5 symbol sets, graphics 160x96 px
<li> Storage: SD-card
<li> Keyboard: standard PS/2 + PS/2 mouse
<li> Printer: YES, serial or LPT
<li> Interfaces: RS-232, UART, Ethernet, GPIO, CAN (option)
<li> Real time clock with battery
<li> Single-tone melody generator with built-in speaker
<li> Hardware emulation: VT100, Robotron 1715, Kaypro, Microbee, TRS-80, ...
</ul>

8-bit Microchip AVR MCUs based, DIP components only (!), 100% open project, programmers and technical support website. Pocket-size box 140x110x35 mm, AC/DC module on the board. Just plug it to the power line, plugin standard VGA monitor or TV and PS/2 keyboard and start to enjoy it!

Please find more info at:
<ul>
<li> http://discord.gg/TZgxdAmskw - worldwide community of CRISS users and followers
<li> https://hackaday.io/project/181038 - project page at HACKADAY.IO, don't forget to like project!
<li> http://www.criss.fun - programmer's and user's manuals and technical reference in English
<li> http://criss.radio.ru - сайт технической поддержки на русском языке
</ul>

It is 100% open project and you can use it as you want without any restrictions, the only thing I would ask: please preserve "CRISS" in the name in your projects! Reference to the original project will be appreciated! 
  
<h2>Project structure</h2>

CRISS CP/M computer contains 4 AVR MCU: 2 (ATTINY13 + ATMEGA328P) are for generating VGA output, 1 (ATMEGA328P) is used as a peripheral controller and 1 (ATMEGA1284P) as main CPU. All MEGA MCUs have bootloaders that should be pre-programmed before installation. Main firmware are uploading via the internal socket using special tool program for that.

<table border=1>
  <tr><th>Role</th><th>Name</th><th>Type</th><th>Bootloader folder</th><th>Firmware folder</th><th>Comments</th></tr>
  <tr><td>VGA controller - sync generation</td><td>VGA-AT13</td><td>ATTINY13A</td><td>-</td><td>VGA-AT13</td><td></td></tr>
  <tr><td>VGA controller - chars generator</td><td>VGA-M328P</td><td>ATMEGA328P</td><td>BOOTLOADERS/VGA</td><td>FIRMWARE/VGA<br>FIRMWARE/VGA-FONTS</td><td></td></tr>
  <tr><td>Pripheral controller</td><td>CPD</td><td>ATMEGA328P</td><td>BOOTLOADERS/CPD</td><td>FIRMWARE/CPD</td><td></td></tr>
  <tr><td>Main CPU</td><td>CPU</td><td>ATMEGA1284P</td><td>BOOTLOADERS/CPU</td><td>FIRMWARE/CPU</td><td></td></tr>
  <tr><td>VGA Coloring</td><td>CLR</td><td>ATTINY84</td><td>BOOTLOADERS/CLR</td><td>FIRMWARE/CLR</td><td></td></tr>
</table>  

