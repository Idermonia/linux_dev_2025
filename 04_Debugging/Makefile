CC = gcc
CFLAGS = -O0 -g -Wall -Wextra
TARGET = range

SCENARIO1 = scenario1.gdb
SCENARIO2 = scenario2.gdb
REF1 = reference1.txt
REF2 = reference2.txt
OUT1 = output1.txt
OUT2 = output2.txt

all: $(TARGET)

$(TARGET): range.c
	$(CC) $(CFLAGS) -o $(TARGET) range.c


test1: $(TARGET)
	@gdb --batch --quiet -x $(SCENARIO1) ./$(TARGET) 2>/dev/null | grep "^@@@" > $(OUT1) || true
	@if diff -u $(REF1) $(OUT1) > /dev/null; then \
		echo "Scenario 1: PASSED"; \
	else \
		echo "Scenario 1: FAILED"; \
		echo "Differences:"; \
		diff -u $(REF1) $(OUT1) || true; \
	fi

test2: $(TARGET)
	@gdb --batch --quiet -x $(SCENARIO2) ./$(TARGET) 2>/dev/null | grep "^@@@" > $(OUT2) || true
	@if diff -u $(REF2) $(OUT2) > /dev/null; then \
		echo "Scenario 2: PASSED"; \
	else \
		echo "Scenario 2: FAILED"; \
		echo "Differences:"; \
		diff -u $(REF2) $(OUT2) || true; \
	fi

test: test1 test2

clean:
	rm -f $(TARGET) $(OUT1) $(OUT2) *.o

.PHONY: all test test1 test2 clean
