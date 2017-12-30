###############################################################################
#                                  board.mk                                   #
#     Licensed under the Apache License, Version 2.0 (the "License")          #
###############################################################################

#----------------------------------------------------------------------------
ifeq ($(BOARD),AD7124_SHIELD)

# List any extra directories to look for include files here.
#     Each directory must be seperated by a space.
#     Use forward slashes for directory separators.
#     For a directory that has spaces, enclose it in quotes.
#VPATH+=:$(PROJECT_TOPDIR)


# AVRIO BOARD directory
AVRIOBRDDIR = $(PROJECT_TOPDIR)/board

# MCU name
ifeq ($(MCU),)
# !! You must change the following setting to match your target board !!
MCU = atmega328p
endif

# Processor frequency.
#     This will define a symbol, F_CPU, in all source code files equal to the
#     processor frequency. You can then use this symbol in your source code to
#     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
#     automatically to create a 32-bit value in your source code.
#     Typical values are:
#         F_CPU =  1000000
#         F_CPU =  1843200
#         F_CPU =  2000000
#         F_CPU =  3686400
#         F_CPU =  4000000
#         F_CPU =  7372800
#         F_CPU =  8000000
#         F_CPU = 11059200
#         F_CPU = 14745600
#         F_CPU = 16000000
#         F_CPU = 18432000
#         F_CPU = 20000000
ifeq ($(F_CPU),)
# !! You must change the following setting to match your target board !!
F_CPU = 16000000
endif

#---------------- External Memory Options ----------------

# 64 KB of external RAM, starting after internal RAM (ATmega128!),
# used for variables (.data/.bss) and heap (malloc()).
#EXTMEMOPTS = -Wl,-Tdata=0x801100,--defsym=__heap_end=0x80ffff

# 64 KB of external RAM, starting after internal RAM (ATmega128!),
# only used for heap (malloc()).
#EXTMEMOPTS = -Wl,--section-start,.data=0x801100,--defsym=__heap_end=0x80ffff

EXTMEMOPTS =

#---------------- Programming Options (avrdude) ----------------
# Programming hardware
# Type: avrdude -c ?
# to get a full listing.
#

# !! You must change and enable the setting below to match your programmer !!


# ATMEL ICE 
#AVRDUDE_PROGRAMMER  = atmelice
AVRDUDE_PROGRAMMER  = atmelice_isp
#AVRDUDE_PROGRAMMER  = atmelice_dw
AVRDUDE_PORT = usb

# AVR Dragon ISP
#AVRDUDE_PROGRAMMER = dragon_isp
#AVRDUDE_PORT = usb

# AVR Dragon JTAG
#AVRDUDE_PROGRAMMER = dragon_jtag
#AVRDUDE_PORT = usb

# JTAG ICE MkII
#AVRDUDE_PROGRAMMER  = jtag2
#AVRDUDE_PORT = usb

# Arduino OnBoard Programmer
#AVRDUDE_PROGRAMMER = arduino
#AVRDUDE_PORT = /dev/ttyACM0
#AVRDUDE_PORT = COM4

# STK200 programmer on parallel port
#AVRDUDE_PROGRAMMER = stk200
#AVRDUDE_PORT = lpt1

# Fuses and lock for fuse target
# !! You may change the following setting to match your target board !!
#AVRDUDE_LFUSE = 0xD2
#AVRDUDE_HFUSE = 0xD9
#AVRDUDE_EFUSE = 0x01
#AVRDUDE_LOCK  = 0xFF

# Set the DEBUG_UI to either gdb or insight.
#DEBUG_UI = gdb
DEBUG_UI = cgdb
#DEBUG_UI = insight

# Set the debugging back-end to either avarice, simulavr.
DEBUG_BACKEND = avarice
#DEBUG_BACKEND = simulavr

JTAG_DEV = usb
AVARICE_BITRATE = --jtag-bitrate 2MHz
AVARICE_OPT = --dragon 
#AVARICE_OPT = --mkII

#----------------------------------------------------------------------------
endif
