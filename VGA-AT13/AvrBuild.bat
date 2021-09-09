@ECHO OFF
"C:\Program Files (x86)\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "C:\D\vga\at13\labels.tmp" -fI -W+ie -C V2 -o "C:\D\vga\at13\at13.hex" -d "C:\D\vga\at13\at13.obj" -e "C:\D\vga\at13\at13.eep" -m "C:\D\vga\at13\at13.map" "C:\D\vga\at13\at13.asm"
