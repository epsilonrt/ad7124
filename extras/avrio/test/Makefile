# Hey Emacs, this is a -*- makefile -*-
#----------------------------------------------------------------------------
SUBDIRS  = led spi ad7124
CLEANER_SUBDIRS = 

all: $(SUBDIRS)
clean: $(SUBDIRS) $(CLEANER_SUBDIRS)
distclean: $(SUBDIRS) $(CLEANER_SUBDIRS)
rebuild: $(SUBDIRS)
lib: $(SUBDIRS)
cleanlib: $(SUBDIRS)
extcoff: $(SUBDIRS)
program: $(SUBDIRS)
debug: $(SUBDIRS)

elf: $(SUBDIRS)
hex: $(SUBDIRS)
eep: $(SUBDIRS)
lss: $(SUBDIRS)
sym: $(SUBDIRS)
har: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -w -C $@ $(MAKECMDGOALS)

$(CLEANER_SUBDIRS):
	$(MAKE) -w -C $@ $(MAKECMDGOALS)

.PHONY: all clean distclean rebuild lib cleanlib extcoff program debug elf hex eep lss sym har $(SUBDIRS) $(CLEANER_SUBDIRS)
