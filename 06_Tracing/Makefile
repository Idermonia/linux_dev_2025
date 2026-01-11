CC = gcc
CFLAGS = -Wall
LDFLAGS = -ldl

all: move protect.so

move: move.c
	$(CC) $(CFLAGS) -o move move.c

protect.so: protect.c
	$(CC) $(CFLAGS) -fPIC -shared -o protect.so protect.c $(LDFLAGS)

test: move protect.so
	@echo "\n=== Test 1: Normal operation ==="
	@echo "test content" > test1_in.txt
	@./move test1_in.txt test1_out.txt
	@[ -f test1_out.txt ] && ! [ -f test1_in.txt ] && echo "PASS" || echo "FAIL"
	@cat test1_out.txt
	@echo "\n=== Test 2: Error injection - stat fails ==="
	@echo "test" > test2_in.txt
	@strace -e inject=stat:error=ENOENT ./move test2_in.txt test2_out.txt 2>/dev/null || true
	@[ -f test2_in.txt ] && echo "PASS" || echo "FAIL"
	@echo "\n=== Test 3: Error injection - open infile fails ==="
	@echo "test" > test3_in.txt
	@strace -e inject=openat:error=EACCES:when=3 ./move test3_in.txt test3_out.txt 2>/dev/null || true
	@[ -f test3_in.txt ] && ! [ -f test3_out.txt ] && echo "PASS" || echo "FAIL"
	@echo "\n=== Test 4: Error injection - open outfile fails ==="
	@echo "test" > test4_in.txt
	@strace -e inject=openat:error=EACCES:when=4 ./move test4_in.txt test4_out.txt 2>/dev/null || true
	@[ -f test4_in.txt ] && echo "PASS" || echo "FAIL"
	@echo "\n=== Test 5: Error injection - read fails ==="
	@echo "content" > test5_in.txt
	@strace -e inject=read:error=EIO ./move test5_in.txt test5_out.txt 2>/dev/null || true
	@[ -f test5_in.txt ] && ! [ -f test5_out.txt ] && echo "PASS" || echo "FAIL"
	@echo "\n=== Test 6: Error injection - write fails ==="
	@echo "content" > test6_in.txt
	@strace -e inject=write:error=ENOSPC ./move test6_in.txt test6_out.txt 2>/dev/null || true
	@[ -f test6_in.txt ] && ! [ -f test6_out.txt ] && echo "PASS" || echo "FAIL"
	@echo "\n=== Test 7: Error injection - close outfile fails ==="
	@echo "content" > test7_in.txt
	@strace -e inject=close:error=EIO:when=3 ./move test7_in.txt test7_out.txt 2>/dev/null || true
	@[ -f test7_in.txt ] && ! [ -f test7_out.txt ] && echo "PASS" || echo "FAIL"
	@echo "\n=== Test 8: Error injection - unlink infile fails ==="
	@echo "content" > test8_in.txt
	@strace -e inject=unlink:error=EACCES ./move test8_in.txt test8_out.txt 2>/dev/null || true
	@[ -f test8_in.txt ] && [ -f test8_out.txt ] && echo "PASS" || echo "FAIL"
	@echo "\n=== Test 9: LD_PRELOAD protection ==="
	@echo "protected content" > test9_PROTECT.txt
	@LD_PRELOAD=./protect.so ./move test9_PROTECT.txt test9_out.txt
	@[ -f test9_PROTECT.txt ] && [ -f test9_out.txt ] && echo "PASS" || echo "FAIL"
	@rm -f test*.txt

clean:
	rm -f move protect.so
	rm -f *.txt

.PHONY: all test clean
