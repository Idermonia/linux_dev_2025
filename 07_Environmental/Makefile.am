bin_PROGRAMS = rhasher
rhasher_SOURCES = rhasher.c
LIBS = -lrhash

if USE_READLINE
LIBS += -lreadline
endif

TESTS = test.sh
EXTRA_DIST = $(TESTS)
