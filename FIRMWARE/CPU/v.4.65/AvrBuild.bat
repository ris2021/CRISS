@ECHO OFF
"C:\Program Files (x86)\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "labels.tmp" -fI -W+ie -C V2E -o "cpu.hex" -d "cpu.obj" -e "cpu.eep" -m "cpu.map" "cpu.asm" -l "cpu.lst"
del /q cpu.obj
e.bat cpu.hex
