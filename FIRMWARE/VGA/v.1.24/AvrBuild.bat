@ECHO OFF
"C:\Program Files (x86)\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "labels.tmp" -fI -W+ie -C V2E -o "vga_328.hex" -d "vga_328.obj" -e "vga_328.eep" -m "vga_328.map" "vga_328.asm"
del vga_328.obj
e.bat vga_328.hex
