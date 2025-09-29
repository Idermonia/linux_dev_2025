.PHONY: clean all distclean
CFLAGS = -Wall -fPIC
GENERATES = prog prog-a prog-so README
TRASH = *.o *~ o.* *.a *.so outfile*

%.o:     %.c
	cc $< $(CFLAGS) -c -o $@

all:     README prog prog-a prog-so

prog:    const.o fun.o prog.o
	cc $^ -o $@

prog-a:  prog.o liboutput_static.a
	cc -static -o prog-a prog.o -L. -loutput_static

prog-so: prog.o liboutput.so
	cc -L. prog.o -loutput -o prog-so

liboutput_static.a: fun.o const.o
	ar rcs liboutput_static.a const.o fun.o

liboutput.so: fun.o const.o
	cc -shared fun.o const.o -o liboutput.so	

fun.o:  outlib.h

README: prog
	./$< 2> $@

test: prog prog-a prog-so
	./prog > outfile0 2>&1
	./prog-a > outfile0-a 2>&1
	LD_LIBRARY_PATH=./ ./prog-so > outfile0-so 2>&1
	cmp outfile0 outfile0-a
	cmp outfile0 outfile0-so
	cmp outfile0-a outfile0-so
	./prog > outfile1 test 2>&1
	./prog-a > outfile1-a test 2>&1
	LD_LIBRARY_PATH=./ ./prog-so > outfile1-so test 2>&1
	cmp outfile1 outfile1-a
	cmp outfile1 outfile1-so
	cmp outfile1-a outfile1-so
	./prog > outfile3 123 456 789 2>&1
	./prog-a > outfile3-a 123 456 789 2>&1
	LD_LIBRARY_PATH=./ ./prog-so > outfile3-so 123 456 789 2>&1
	cmp outfile3 outfile3-a
	cmp outfile3 outfile3-so
	cmp outfile3-a outfile3-so

clean:
	rm -f $(TRASH)

distclean:      clean
	rm -rf $(GENERATES)
