CC = gcc

FLAGS = -Wall -Wextra -Werror -std=c11 -fanalyzer -pedantic

ADDITIONAL_FLAGS = -lcheck
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	ADDITIONAL_FLAGS += -lsubunit -lm
endif
#ifeq ($(UNAME_S),Darwin)
#	something for MACOS
#endif

SRC_C_FILES = lib/*.c
SRC_H_FILES = s21_decimal.h

TEST_C_FILES = tests/*.c
TEST_H_FILES = tests/s21_decimal_testing.h

TEST_TARGET  = s21_test

LIB = s21_decimal.a

REPORT_DIR = report

apply_clang: 
	cp ../materials/linters/.clang-format .
	clang-format -i *.[ch]
	clang-format -i */*.[ch]
	rm -f .clang-format

all: clean gcov_report $(LIB) test

test: apply_clang $(SRC_C_FILES) $(SRC_H_FILES)
	$(CC) $(FLAGS) $(SRC_C_FILES) $(SRC_H_FILES) $(TEST_C_FILES) $(TEST_H_FILES) -o $(TEST_TARGET) $(ADDITIONAL_FLAGS)
	./$(TEST_TARGET)

random_tests: apply_clang $(SRC_C_FILES) $(SRC_H_FILES)
	$(CC) $(FLAGS) $(SRC_C_FILES) $(SRC_H_FILES) $(RANDOM_TESTS_FILE) $(TEST_H_FILES) -o $(TEST_TARGET) $(ADDITIONAL_FLAGS)
	./$(TEST_TARGET)

gcov_report: apply_clang
	$(CC) --coverage $(FLAGS) $(SRC_C_FILES) $(TEST_C_FILES) -o $(TEST_TARGET) $(ADDITIONAL_FLAGS)
	./$(TEST_TARGET)
	lcov -t "$(TEST_TARGET)" -o $(TEST_TARGET).info -c -d .
	genhtml -o report $(TEST_TARGET).info
	rm *.gcda *.gcno *.info

$(LIB): apply_clang
	$(CC) -c $(SRC_C_FILES) $(ADDITIONAL_FLAGS)
	ar rcv $(LIB) *.o
	ranlib $(LIB)
	rm *.o

clean_test:
	rm -f $(TEST_TARGET)

clean_report:
	rm -rf $(REPORT_DIR)

clean_lib:
	rm -f $(LIB)

clean_obj:
	rm -f *.o

clean_gcov:
	rm -f *.gc*

clean: clean_test clean_report clean_lib clean_obj clean_gcov
