EEPROM_INIT:
	jmp	_EEPROM_INIT
EEPROM_CMD:
	jmp	_EEPROM_CMD	
	; exec port cmd command







; startup LAN Init
_EEPROM_INIT: 
;        iSPI	0xff		; soft reset
	ret


_EEPROM_CMD:
	lds	FROMRAM0, HW_FOUND
	sbrs	FROMRAM0, HW_FOUND_ROM
	jmp	SPCMD_notfound

        tcbe	0, _EEPROM_INIT
	ret
;