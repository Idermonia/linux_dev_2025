all-local: ru/LC_MESSAGES/guess.mo

ru/LC_MESSAGES/guess.mo: ru.po
	mkdir -p ru/LC_MESSAGES
	msgfmt -o ru/LC_MESSAGES/guess.mo ru.po

install-data-local:
	$(MKDIR_P) $(DESTDIR)$(localedir)/ru/LC_MESSAGES
	cp -f ru/LC_MESSAGES/guess.mo $(DESTDIR)$(localedir)/ru/LC_MESSAGES/
	
uninstall-local:
	rm -f $(DESTDIR)$(localedir)/ru/LC_MESSAGES/guess.mo

clean-local:
	rm -rf ru
