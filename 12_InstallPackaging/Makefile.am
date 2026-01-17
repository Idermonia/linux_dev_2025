SUBDIRS = src po tests

EXTRA_DIST = README.md

@DX_RULES@

all-local: doxygen-doc

install-data-local:
	mkdir -p $(DESTDIR)/$(docdir)
	cp -a doxygen-doc/html $(DESTDIR)/$(docdir)
	
install-data-local:
	$(MKDIR_P) $(DESTDIR)$(docdir)/html
	cp -a doxygen-doc/html/* $(DESTDIR)$(docdir)/html/
	
	$(MKDIR_P) $(DESTDIR)$(mandir)/man1
	cp -a doxygen-doc/man/man1/* $(DESTDIR)$(mandir)/man1/
	
uninstall-local:
	rm -rf $(DESTDIR)$(docdir)/html
	rm -f $(DESTDIR)$(mandir)/man1/guess.1

doxygen-doc/man/man1/guess.1:	doxygen-doc

man1_MANS = doxygen-doc/man/man1/guess.1

clean-local: doxygen-clean
