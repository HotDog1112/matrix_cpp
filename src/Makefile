CC=g++
FLAGS=-Wall -Werror -Wextra -std=c++17 -pedantic -pthread
SOURCES=s21_matrix_oop.cc
OBJECTS=*.o
TESTFLAGS=-lgtest
DELETE=rm -rf
OBJ= s21_matrix_oop.o

all: gcov_report

s21_matrix_oop.a:
	$(CC) -c $(FLAGS) $(SOURCES) -o $(OBJ)
	ar -rc s21_matrix_oop.a $(OBJ)
	ranlib s21_matrix_oop.a

test: s21_matrix_oop.a
	$(CC) $(FLAGS) s21_matrix+_tests.cc s21_matrix_oop.a -o s21_m_oop $(TESTFLAGS)
	./s21_m_oop

gcov_report: clean
	$(CC) -c $(FLAGS) s21_matrix+_tests.cc -o s21_matrix+_tests.o
	ar -rcs s21_matrix+_tests.a s21_matrix+_tests.o
	$(CC) -coverage $(SOURCES) s21_matrix+_tests.a -o s21_m_oop $(TESTFLAGS)
	./s21_m_oop
	lcov -t "s21_m_oop" -o report.info -c -d .
	genhtml -o report.html report.info
	rm *.gcda *.gcno
	open report.html/index.html 2>/dev/null

clean:
	$(DELETE) *.a *.o s21_matrix_oop.a *.gcno *.gcda *.info s21_m_oop *.css *.html report
	
leaks:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./s21_m_oop

linter:
	clang-format -i *.cc *.h
	clang-format -n *.cc *.h

.PHONY: leaks linter clean all
