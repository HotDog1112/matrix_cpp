CC=gcc -lstdc++
CFLAGS=-c -Wall -Wextra -std=c++17
# LINUXCFLAGS=-lcheck -lm -lsubunit -lrt -lpthread
TESTFLAGS=-lgtest
SOURCES=s21_matrix_oop.cc
OBJECTS=*.o
DELETE=rm -rf

all: s21_matrix_oop.a test gcov_report


s21_matrix_oop.a:
	$(CC) $(CFLAGS) $(SOURCES)
	ar rcs s21_matrix_oop.a s21_matrix_oop.o
	$(DELETE) $(OBJECTS)

test: s21_matrix_oop.a
	$(CC) s21_matrix+_tests.cc s21_matrix_oop.a  -o tests.out $(TESTFLAGS)
	# $(CC) --coverage $(CFLAGS) -o test_cases s21_matrix_oop.a s21_matrix+_tests.a $(SOURCES) $(TESTFLAGS) 
	./tests.out

# test: s21_matrix_oop.a
# 	$(CC) -g -c s21_matrix+_tests.cc
# 	ar rc s21_matrix+_tests.a s21_matrix+_tests.o
# 	ranlib s21_matrix+_tests.a
# 	$(CC) --coverage $(CFLAGS)  -o test_cases s21_matrix_oop.a s21_matrix+_tests.a $(SOURCES) $(TESTFLAGS) 
# 	./test_cases

clean:
	$(DELETE) *.a *.html *.o *.gcda *.gcno *.css *.out

gcov_report: test
	gcovr -r . --html --html-details -o report.html
	rm *.gcda *.gcno
	open report.html

linter:
	clang-format -i *.cc
	clang-format -i *.h
	clang-format -n *.cc *.h

leaks:
	leaks --atExit -- ./s21_matrix_oop

.PHONY: all clean
