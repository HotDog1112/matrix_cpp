CC=gcc -lstdc++
CFLAGS=-c -Wall -Wextra -std=c++17
# LINUXCFLAGS=-lcheck -lm -lsubunit -lrt -lpthread
TESTFLAGS=-lgtest -lgmock
SOURCES=s21_matrix_oop.cc
OBJECTS=*.o
DELETE=rm -rf

all: s21_matrix_oop.a test


s21_matrix_oop.a:
	$(CC) $(CFLAGS) $(SOURCES)
	ar rcs s21_matrix_oop.a s21_matrix_oop.o
	$(DELETE) $(OBJECTS)

test: s21_matrix_oop.a
	$(CC) s21_matrix+_tests.cc s21_matrix_oop.a -o tests.out $(TESTFLAGS)
	./tests.out

clean:
	$(DELETE) *.a *.html *.o *.gcda *.gcno *.css *.out

# gcov_report: s21_matrix_oop.a_for_tests
# 	$(CC) $(CFLAGS) $(SOURCES) s21_matrix+_tests.o -o matrix_test.out $(TESTFLAGS)
# 	./matrix_test.out
# 	gcovr -r . --html --html-details -o report.html
# 	rm *.gcda *.gcno
# 	open report.html

# s21_matrix_oop.a_for_tests:
# 	$(CC) -coverage $(CFLAGS) s21_matrix+_tests.cc $(TESTFLAGS)

.PHONY: all clean
