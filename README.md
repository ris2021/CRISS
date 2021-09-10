<h1 color=red>Migration to Github is under progress and will take a while, please wait for the completion!</h1>

<h1>CRISS CP/M Project</h1>

CRISS CP/M: the modern single-board 8-bit full-featured personal computer! Amazing functionality for the DIY device: it is not a toy, it is REAL Computer, the SAFEST computer in the world and the sophisticated control platform for your projects!

<h2>Features:</h2>

<ul>
<li> OS: CP/M 2.2 = programming languages, text processors, games, business software, etc.
<li> Instructions: Z80 (Zilog), extended with MUL, DIV, and floating-point, control time 1us LD r,r ops
<li> Memory: 64Kb SRAM, 128 Kb EPROM
<li> Video: VGA (!), monochrome, up to 25x80 chars, 5 symbols sets, graphic 160x96 px
<li> Storage: SD-card
<li> Keyboard: standard PS/2
<li> Printer: YES, serial or LPT
<li> Interfaces: RS-232, UART, Ethernet, GPIO, CAN (option)
<li> Real time clock with battery
<li> Single-tone melody generator with built-in speaker
<li> Hardware emulation: Robotron 1715, Kaypro, Microbee, TRS-80, ...
</ul>

8-bit Microchip AVR MCUs based, DIP components only (!), 100% open project, programmers and technical support website. Pocket-size box 140x110x35 mm, AC/DC module on the board. Just plug it to the power line, plugin standard VGA monitor or TV and PS/2 keyboard and start to enjoy it!

Please find more info at www.criss.fun, criss.radio.ru

<h2>Project structure</h2>

CRISS CP/M computer contains 4 AVR MCU: two for VGA driver, 1 as peripherial controller and 1 as main CPU. Firmware for them consists from bootloader that must be pre-programming before soldering and the firmware.

<table border=1>
  <tr><th>Role</th><th>Name</th><th>Type</th><th>Bootloader folder</th><th>Firmware folder</th><th>Fuses</th><th>Comments</th></tr>
  <tr><td>VGA cobtroller - sync generation</td><td>VGA-AT13</td><td>ATTINY13A</td><td>-</td><td>VGA-AT13</td><td></td><td></td></tr>
  <tr><td>VGA cobtroller - chars generator</td><td>VGA-M328</td><td>ATMEGA328P</td><td>VGA-M328-BL</td><td>VGA-M328-FW</td><td></td><td></td></tr>
  <tr><td>Pripherial controller</td><td>CPD</td><td>ATMEGA328P</td><td>CPD-BL</td><td>CPD-FW</td><td></td><td></td></tr>
  <tr><td>Main CPU</td><td>CPU</td><td>ATMEGA1284P</td><td>CPU-BL</td><td>CPD-FW</td><td></td><td></td></tr>
</table>  

