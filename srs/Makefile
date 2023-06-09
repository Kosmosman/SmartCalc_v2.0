CC = g++
STD = -std=c++17 -lstdc++
STD_FLAGS = -Wall -Wextra -Werror
TEST_FLAGS = -lgtest
TEST_SRC = UnitTest/tests.cc Model/parcer.cc

all: clean install test dvi open

install:
	mkdir build
	cd build && cmake .. && make

uninstall:
	rm -rf build

dist: clean
	tar -cvf SmartCalc_v2.tar *

dvi:
	open dvi.html

open:
	./build/SmartCalc_v2.app/Contents/MacOS/SmartCalc_v2

test:
	rm -rf test
	$(CC) $(STD) $(STD_FLAGS) $(TEST_SRC) -o test $(TEST_FLAGS)
	leaks -atExit -- ./test

leaks:
	leaks -atExit -- ./build/SmartCalc_v2.app/Contents/MacOS/SmartCalc_v2

style:
	cp ../materials/linters/.clang-format .
	clang-format -n -style=Google Controller/* Model/* View/*.h View/*.cc
	rm -f .clang-format

clean_test:
	rm -rf test

clean: clean_test
	rm -rf build
	