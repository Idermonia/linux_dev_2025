lib_LTLIBRARIES = libroman.la
libroman_la_SOURCES = roman.c
include_HEADERS = roman.h
libroman_la_LDFLAGS = -version-info 1:0:0


bin_PROGRAMS = guess
guess_SOURCES = guess.c
guess_LDADD = libroman.la

guess_CFLAGS = -DLOCALEDIR=\"$(localedir)\"

