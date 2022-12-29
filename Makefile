#-------------------------------------------------------
#    Узнаем какая ОС, Присваиваем значение флагов
#-------------------------------------------------------

OS = $(shell uname)
ifeq ("$(OS)", "Linux")
    TEST_FLAGS = -lcheck  -pthread -lrt -lm -lsubunit
    LEAKS_RUN = valgrind ./test
else
    TEST_FLAGS = -lcheck
    LEAKS_RUN = leaks -atExit -- ./test
endif

FLAGS = -Wall -Wextra -Werror -std=c11
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

#-------------------------------------------------------
#    Переменная для компилятора
#-------------------------------------------------------

CC = gcc

#-------------------------------------------------------
#    Ищем файлы для библиотекиб делаем переменную
#    Переименовываем для объектных файлов
#-------------------------------------------------------

SRCS = $(wildcard s21*.c)
OBJ_FILES = $(patsubst %.c,%.o,$(SRCS))

#-------------------------------------------------------
#    Переменная которая указывает на наш Makefile
#-------------------------------------------------------

THIS_FILE := $(lastword $(MAKEFILE_LIST))

#-------------------------------------------------------
#    Переменная для создания каталога report
#-------------------------------------------------------

REPORT = @mkdir -p report

#-------------------------------------------------------
#    Цели
#-------------------------------------------------------

all: clean s21_math.a gcov_report

tests.c: s21_math_tests
	checkmk ./tests/s21_math_tests > tests.c

s21_math_tests: ./tests/s21_tests_header ./tests/s21_test_*
	cat  ./tests/s21_tests_header ./tests/s21_test_* > ./tests/s21_math_tests

test: tests.c $(SRCS)
	$(CC) tests.c $(SRCS) $(FLAGS) $(TEST_FLAGS) $(GCOV_FLAGS) -o test
	./test

gcov_report: test
	$(REPORT)
	gcovr -r . --html --html-details -o report/report.html
	@$(MAKE) -f $(THIS_FILE) clean_src
	
s21_math.a: $(OBJ_FILES)
	ar rcs s21_math.a $(OBJ_FILES)
	ranlib s21_math.a
	
%.o:%.c
	$(CC) -c $(FLAGS) $< -o $@ -I .

clean_src:
	rm -rf *.o  *.gcda *.gcno *.gcov

clean: clean_src
	rm -rf report *.a test tests.c

leaks: test
	$(LEAKS_RUN)
	@$(MAKE) -f $(THIS_FILE) clean_src

cpplint:
	@python3 ../materials/linters/cpplint.py --extensions=c *.c *.h
