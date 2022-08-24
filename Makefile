CC = g++ -std=c++17 -Wall -Wextra -Werror
SOURCE = $(wildcard backend/*.cpp) $(wildcard frontend/*.cpp)
HEADERS = $(wildcard backend/*.h) $(wildcard frontend/*.h)

all: install tests
install:
	mkdir build
	qmake ./qtcalc_plus.pro -o ./build/Makefile_qt
	cd build && make -f Makefile_qt

uninstall:
	rm -rf *.gcno *.gcda *.info report distr *.out CalcNew.app build *.gz

dvi:
	open dvi.html

tests:
	$(CC) backend/model.cpp tests.cpp -o testing.out -lgtest -lgtest_main
	./testing.out

clean:
	rm -rf *.out *.o *.a
	rm -rf *.gcda *.gcno *.info
	rm -rf report s21_test
	rm -rf *.tgz s21_test
	rm -rf ./build*

rebuild: clean all
