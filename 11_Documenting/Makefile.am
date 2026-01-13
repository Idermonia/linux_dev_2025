SUBDIRS = src po

@DX_RULES@

all-local: doxygen-doc po/ru/LC_MESSAGES/guess.mo

install-data-local:
	mkdir -p $(DESTDIR)/$(docdir)
	cp -a doxygen-doc/html $(DESTDIR)/$(docdir)
	
doxygen-doc/man/man1/guess.1:	doxygen-doc

man1_MANS = doxygen-doc/man/man1/guess.1
