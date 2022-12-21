CC = gcc -lstdc++
FLAGS= -Wall -Werror -Wextra -std=c++17 -pedantic
SOURCES = s21_matrix_oop.cc
OBJECTS = *.o
TESTFLAGS=-lgtest
DELETE=rm -rf

all: gcov_report

s21_matrix_oop.a:
	$(CC) -c $(FLAGS) $(SOURCES) -o $(OBJ_OOP_O)
	ar -rc s21_matrix_oop.a $(OBJ_OOP_O)
	ranlib s21_matrix_oop.a

test: s21_matrix_oop.a
	$(CC) $(FLAGS) s21_matrix+_tests.cc s21_matrix_oop.a -o s21_m_oop $(TESTFLAGS)
	./s21_m_oop

gcov_report: clean
	$(CC) -c $(FLAGS) s21_matrix+_tests.cc -o s21_matrix+_tests.o
	ar -rcs s21_matrix+_tests.a s21_matrix+_tests.o
	$(CC) -coverage $(SOURCES) s21_matrix+_tests.a -o s21_m_oop $(TESTFLAGS)
	./s21_m_oop
	gcovr -r . --html --html-details -o report.html
	rm *.gcda *.gcno
	open report.html

clean:
	$(DELETE) *.a *.o s21_matrix_oop.a *.gcno *.gcda *.info s21_m_oop *.css *.html
	$(DELETE) report

leaks:
	leaks --atExit -- ./s21_m_oop

linter:
	clang-format -i *.cc *.h
	clang-format -n *.cc *.h

.PHONY: leaks linter clean all