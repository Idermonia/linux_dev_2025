CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = esub
SOURCES = esub.c

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET) test_output.txt sed_output.txt

test: $(TARGET)
	@echo "=== Тест 1 ==="
	@./$(TARGET) "hello" "world" "hello there" > test_output.txt
	@echo "hello there" | sed -E "s/hello/world/" > sed_output.txt
	@diff test_output.txt sed_output.txt && echo "PASS" || echo "FAIL"
	
	@echo "=== Тест 2 ==="
	@./$(TARGET) "(hello) (world)" "\2, \1!" "hello world" > test_output.txt
	@echo "hello world" | sed -E "s/(hello) (world)/\2, \1!/" > sed_output.txt
	@diff test_output.txt sed_output.txt && echo "PASS" || echo "FAIL"
	
	@echo "=== Тест 3: ==="
	@./$(TARGET) "path" "C:\\\\home" "path" > test_output.txt
	@echo "path" | sed -E "s/path/C:\\\\home/" > sed_output.txt
	@diff test_output.txt sed_output.txt && echo "PASS" || echo "FAIL"
	
	@echo "=== Тест 4: ==="
	@./$(TARGET) "a(.)c(.)e" "1\12\2" "aXcYe" > test_output.txt
	@echo "aXcYe" | sed -E "s/a(.)c(.)e/1\12\2/" > sed_output.txt
	@diff test_output.txt sed_output.txt && echo "PASS" || echo "FAIL"
	
	@echo "=== Тест 5:  ==="
	@./$(TARGET) "nomatch" "replacement" "hello world" > test_output.txt
	@echo "hello world" | sed -E "s/nomatch/replacement/" > sed_output.txt
	@diff test_output.txt sed_output.txt && echo "PASS" || echo "FAIL"
	
	@echo "=== Тест 6: ==="
	@./$(TARGET) "mid" "MIDDLE" "begin mid end" > test_output.txt
	@echo "begin mid end" | sed -E "s/mid/MIDDLE/" > sed_output.txt
	@diff test_output.txt sed_output.txt && echo "PASS" || echo "FAIL"
	
	@rm -f test_output.txt sed_output.txt
