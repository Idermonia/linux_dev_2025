all: maze maze_001 maze_002 maze_003

maze_001.c: maze.c 001.patch
	patch -o maze_001.c maze.c 001.patch

maze_002.c: maze_001.c 002.patch
	patch -o maze_002.c maze_001.c 002.patch

maze_003.c: maze_002.c 003.patch
	patch -o maze_003.c maze_002.c 003.patch


maze: maze.c
	gcc -o maze maze.c

maze_001: maze_001.c
	gcc -o maze_001 maze_001.c

maze_002: maze_002.c
	gcc -o maze_002 maze_002.c

maze_003: maze_003.c
	gcc -o maze_003 maze_003.c

run: all
	@echo "=== Original maze ==="
	./maze
	@echo "=== Version 001 ==="
	./maze_001 4
	@echo "=== Version 002 ==="
	./maze_002 "@ " 4
	@echo "=== Version 003 ==="
	./maze_003 42 "+ " 4

clean:
	rm -f maze maze_001 maze_002 maze_003 maze_001.c maze_002.c maze_003.c

.PHONY: all run clean
