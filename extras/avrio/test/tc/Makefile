# Hey Emacs, this is a -*- makefile -*-
#----------------------------------------------------------------------------
# $Id$
# On command line:
#
# make all = Make software.
#
# make clean = Clean out built project files.
#
# make rebuild = rebuilt project.
#
# make coff = Convert ELF to AVR COFF.
#
# make extcoff = Convert ELF to AVR Extended COFF.
#
# make program = Download the hex file to the device, using avrdude.
#                Please customize the avrdude settings below first!
#
# make debug = Start either simulavr or avarice as specified for debugging,
#              with avr-gdb or avr-insight as the front end for debugging.
#
# make filename.s = Just compile filename.c into the assembler code only.
#
# make filename.i = Create a preprocessed source file for use in submitting
#                   bug reports to the GCC project.

# Nom du fichier cible (sans extension).
TARGET = test_tc

# Chemin relatif du répertoire racine du projet de l'utilisateur
PROJECT_TOPDIR = ../..

# User Project
USER_PROJECT = AD7124_SHIELD

#----------------------------------------------------------------------------
#                               ~~~~AVRIO~~~~
# Chemin relatif du répertoire racine d'AVRIO
AVRIO_TOPDIR = $(abspath $(AVRIO_ROOT))

# Nom de la carte cible (voir le fichier avrio/boards.txt pour la liste)
# Si BOARD est vide, il faut un fichier board.mk pour définir les propriétés de
# la carte dans le répertoire où se trouve ce Makefile !
BOARD = AD7124_SHIELD

# Permet de générer un fichier version-git.h permettant de récupérer les informations sur la version
GIT_VERSION = OFF

# Configuration de AvrIO
# -------------------------------
AVRIO_CONFIG  = __ASSERT_USE_STDERR
AVRIO_CONFIG += AVRIO_TC_ENABLE
#AVRIO_CONFIG += AVRIO_TC_FLAVOUR=TC_FLAVOUR_POLL
AVRIO_CONFIG += AVRIO_TC_FLAVOUR=TC_FLAVOUR_IRQ

# Valide le noyau multitâche temps réel AVRX (sous forme de bibliothèque)
AVRX = OFF

# Valide l'intégration d'Arduino (sous forme de bibliothèque: ON/OFF)
AVRIO_ARDUINO = OFF

#                               ~~~~AVRIO~~~~
#----------------------------------------------------------------------------

# Niveau d'optimisation de GCC =  [0, 1, 2, 3, s].
#     0 = pas d'optimisation (pour debug).
#     s = optimisation de la taille du code (pour release).
#     (Note: 3 n'est pas toujours le meilleur niveau. Voir la FAQ avr-libc.)
OPT = s

# Format informations Debug
#     Les formats natifs pour AVR-GCC -g sont dwarf-2 [default] ou stabs.
#     AVR Studio 4.10 nécessite dwarf-2.
DEBUG_FORMAT = dwarf-2

# Niveau d'optimisation de GCC =  [0, 1, 2, 3, s] pour le debug
#     0 = pas d'optimisation (pour debug).
#     s = optimisation de la taille du code (pour release).
#     (Note: 3 n'est pas toujours le meilleur niveau. Voir la FAQ avr-libc.)
DEBUG_OPT = s

# Retrait des informations Debug (ON/OFF)
# Si défini sur ON, aucune information de debug ne sera générée
#DEBUG = ON

# Affiche la ligne de compilation GCC ou non (ON/OFF)
#VIEW_GCC_LINE = ON

# Désactive la suppression des variables et fonctions "inutiles"
# Le linker vérifie d'une fonction ou une variable est appellée, si ce n'est pas
# le cas, il supprime la variable ou la fonction
# Cela peut être problèmatique dans certains cas (bootloarder !)
DISABLE_DELETE_UNUSED_SECTIONS = OFF

# Liste des fichiers source C. (Les dépendances sont automatiquement générées.)
# Le chemin d'accès des fichiers sources systèmes a été ajouté au chemin de
# recherche du compilateur, il n'est donc pas nécessaire de préciser le chemin
# d'accès complet du fichier mais seulement le nom du projet (avrio, avrx, ...)
SRC  = $(TARGET).c avrio/file.c avrio/tc.c  avrio/dpin.c 
SRC += avrio/tc_poll.c
SRC += avrio/tc_irq.c avrio/queue.c

# Liste des fichiers source C++. (Les dépendances sont automatiquement générées.)
# Le chemin d'accès des fichiers sources systèmes a été ajouté au chemin de
# recherche du compilateur, il n'est donc pas nécessaire de préciser le chemin
# d'accès complet du fichier mais seulement le nom du projet (avrio, avrx, ...)
CPPSRC =

# Liste des fichiers source assembleur
#   L'extenson doit toujours être .S (en majuscule). En effet, les fichiers .s
#   ne sont pas consédérés comme des fichiers sources mais comme des fichiers
#   générés par le compilateur et seront supprimés lors d'un make clean.
#   Cela est valable aussi sous DOS/Windows (bien que le système d'exploitation
#   ne soit pas sensible à la casse).
ASRC  =

# Place -D or -U options here for C sources
CDEFS +=

# Place -D or -U options here for ASM sources
ADEFS =

# Place -D or -U options here for C++ sources
CPPDEFS =

# List any extra directories to look for include files here.
#     Each directory must be seperated by a space.
#     Use forward slashes for directory separators.
#     For a directory that has spaces, enclose it in quotes.
EXTRA_INCDIRS =

#---------------- Library Options ----------------
# List any extra directories to look for libraries here.
#     Each directory must be seperated by a space.
#     Use forward slashes for directory separators.
#     For a directory that has spaces, enclose it in quotes.
EXTRA_LIBDIRS =

# List any extra libraries here.
#     Each library must be seperated by a space.
EXTRA_LIBS =

# STANDARD, MIN or FLOAT
PRINTF_VERSION = STANDARD

# STANDARD, MIN or FLOAT
SCANF_VERSION = STANDARD

# ON/OFF
MATH_LIB_ENABLE = ON

#---------------- Additional Compiler/Assembler Options ----------------
CFLAGS   += -fno-strict-aliasing
CPPFLAGS += 
ASFLAGS  += 
#---------------- Additional Linker Options ----------------
LDFLAGS  +=

##---------------- Programming Options (avrdude) ----------------
# Programming hardware
# Type: avrdude -c ?
# to get a full listing.
#
# STK200 programmer on parallel port
#AVRDUDE_PROGRAMMER = stk200
#AVRDUDE_PORT = lpt1

# JTAG ICE MkII
#AVRDUDE_PROGRAMMER  = jtag2
#AVRDUDE_PORT = usb

# AVR Dragon
#AVRDUDE_PROGRAMMER = dragon_isp
AVRDUDE_PROGRAMMER = dragon_jtag
#AVRDUDE_PROGRAMMER = dragon_dw
AVRDUDE_PORT = usb

# Arduino OnBoard Programmer
#AVRDUDE_PROGRAMMER = arduino
#AVRDUDE_PORT = /dev/ttyACM0
#AVRDUDE_PORT = COM4
#AVRDUDE_BAUDRATE = 115200

# ON/OFF

#---------------- Debugging Options ----------------

# Set the DEBUG_UI to either gdb, cgdb or insight.
#DEBUG_UI = gdb
DEBUG_UI = cgdb
#DEBUG_UI = insight

# Set the debugging back-end to either avarice, simulavr.
DEBUG_BACKEND = avarice
#DEBUG_BACKEND = simulavr

# When using avarice settings for the JTAG
JTAG_DEV = usb

AVARICE_OPT = --dragon 
#AVARICE_OPT = --mkII
AVARICE_BITRATE = --jtag-bitrate 2MHz

#------------------------------------------------------------------------------
include $(AVRIO_TOPDIR)/script/common.mk
