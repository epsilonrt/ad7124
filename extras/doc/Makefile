# Hey Emacs, this is a -*- makefile -*-
#----------------------------------------------------------------------------

PROJECT_NAME = ad7124

# Chemin relatif du répertoire racine de Avrio
PROJECT_TOPDIR = ../..

#---------------- Install Options ----------------
prefix=/usr/local
INSTALL_DOCDIR=$(prefix)/share/doc

MSG_INSTALL = [INSTALL]
MSG_UNINSTALL = [UNINSTALL]
MSG_DOC = [DOC]
MSG_MAIN = [MAINPAGE]
MSG_TAR = [TAR]
MSG_CLEAN = [CLEAN]
MSG_DISTCLEAN = [DISTCLEAN]

all: doc
rebuild: distclean doc
version: version.mk
doc: html

main_page.dox: main_page_header.dox main_page_footer.dox $(PROJECT_TOPDIR)/README.md
	@echo "$(MSG_MAIN)"
	@./build_main_page.sh

version.mk: 
	@git-version $@
#	echo "1.0.0" > version.mk

Doxyfile: Doxyfile.in version.mk 
	@sed  -e "s#GIT_VERSION#$(shell cat version.mk)#g" $< > $@

html: Doxyfile $(PROJECT_TOPDIR)/src/ad7124.h main_page.dox DoxygenLayout.xml
	@echo "$(MSG_DOC) $(@)"
	@doxygen $<

tar: html
	@echo "$(MSG_TAR)"
	@tar czf $(PROJECT_NAME)-doc-html-$(shell cat version.mk).tar.gz html

x-browser: html
	@x-www-browser html/index.html &

browser: html
	@www-browser html/index.html

clean: 
	@echo "$(MSG_CLEAN)"
	@-rm -fr html
	@-rm -f Doxyfile main_page.dox .version version.mk

distclean: clean
	@echo "$(MSG_DISTCLEAN)"
	@-rm -f $(PROJECT_NAME)-doc-html-*.tar.gz
	@-rm -f *.tag *.db

install: tar uninstall
	@echo "$(MSG_INSTALL) $(TARGET) doc in $(INSTALL_DOCDIR)"
	@-install -d -m 0755 $(INSTALL_DOCDIR)/$(PROJECT_NAME)
	@tar xzf $(PROJECT_NAME)-doc-html-$(shell cat version.mk).tar.gz -C $(INSTALL_DOCDIR)/$(PROJECT_NAME) --strip-components=1

uninstall:
	@echo "$(MSG_UNINSTALL) $(TARGET) doc from $(INSTALL_DOCDIR)"
	@-rm -fr $(INSTALL_DOCDIR)/$(PROJECT_NAME)

.PHONY: all doc tar rebuild clean distclean install uninstall version browser x-browser
