    
MSG_WELCOME0:	.DB	13,10,13,10,13,10,13,10
		.DB   	"CRISS CP/M main CPU module, (c) Igor S. Reshetnikov ",13,10 
                .DB	"Version 4.64 AVR Z80+ Emulator",13,10
;		.DB   	"Supported externals: SD card, Real time clock, Ethernet LAN ",13,10 
		.DB   	"CP/M 2.2 compatible",13,10
		.DB	13,10,0,0

MSG_RAMTEST:	.DB   	"64K RAM TEST ... ",0
MSG_PASSED:	.DB   	"Passed, Ok.",13,10,0 
MSG_FAILED:	.DB   	"Failed !!! ",13,10,0 

MSG_RTCDATA:	.DB	"RTC: ",0
MSG_RTCNOTFOUND:.DB	"Chip not found.",13,10,0
MSG_RTCLOADED:	.DB	13,10,"RTC RAM settings loaded",13,10,0

MSG_LANSTATUS:	.DB   	"LAN controller: ",0,0 
MSG_LANPRES:	.DB	"Found, REVID: ",0,0
MSG_LANINITING:	.DB	", Initialising.",13,10,0

MSG_SDSTATUS:	.DB	"SD card storage: Initialising. ",0 

MSG_SELECTOS:	.DB	13,10,"Loading OS image source: ",13,10,0 
MSG_BOOTROM:	.DB	" A or B = EPROM block 1 or 2",13,10,0,0

MSG_SELKEY:	.DB	"Please select boot option: ",0 

MSG_LOADING:	.DB	13,10,"Loading block ",0,0 
MSG_LOADBAD:	.DB	"Bad loading block index",13,10,0 
MSG_LOADSD:	.DB	" from SD-card",13,10,0 
MSG_LOADNOSD:	.DB	"Valid SD-card not found",13,10,0 

;MSG_LOADEPROM:	.DB	"Loading OS image from onboard EPROM",13,10,0 
MSG_STARTING:	.DB	13,10,"Starting from address 0x100",13,0,0 

MSG_SDFOUND:	.DB	"Found bootable SD card, ID: ",0,0		
;		.DB	0,0,0,0

MSG_ROMCHECK:	.DB	"EEPROM: ",0,0		
MSG_ROMFOUND:	.DB	"Found, SREG: ",0

MSG_IRQCTRL:	.DB	"IRQ controller ",0		
MSG_IRQNOTFOUND:.DB	"not found, version CRISS 3.* detected",13,10,0
MSG_IRQFOUND:	.DB	"found, version CRISS PRO 5.* detected",13,10,0		

MSG_ONLYIMG:	.DB	"Only one image found, loading it.",13,10,0		

MSG_CAN:	.DB	"CAN controller found.",13,10,0		

MSG_CPDFOUND:	.DB	"Peripheral controller found",13,10,0
MSG_NOOS:	.DB	"No boot source found, replace SD-card: ",13,10,0
MSG_END:	.DB	0,0,0,0
