bin_PROGRAMS = guess
guess_SOURCES = guess.c
guess_CFLAGS = -Wall

all-local: ru/LC_MESSAGES/guess.mo

ru/LC_MESSAGES/guess.mo: ru.po
	mkdir -p ru/LC_MESSAGES
	msgfmt -o ru/LC_MESSAGES/guess.mo ru.po

update-po: guess.pot
	msgmerge --update ru.po guess.pot

guess.pot: $(guess_SOURCES)
	xgettext --keyword=_ --keyword=gettext -o guess.pot $(guess_SOURCES)


clean-local:
	rm -rf ru
	test -z "guess.pot" || rm -f  guess.pot
