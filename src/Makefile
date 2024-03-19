WWW = -Wall -Werror -Wextra -std=c11
LC=-lcheck
GCOV=-fprofile-arcs -ftest-coverage
UNIX = -lsubunit -lrt -lpthread -lm
SRC=$(wildcard ./back/*.c)
SRC_TEST=test.c
OS=$(shell uname -s)
TARGET=CalculatorC

ifeq ($(OS),Linux)
	OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif

all: clean install

install: 
	@mkdir -p ../build
	@cd front && qmake && make && make clean && rm -rf Makefile && mv CalculatorC.app ../../build/$(TARGET).app
	@cp -R ../build/$(TARGET).app ~/Desktop/$(TARGET).app

uninstall:
	@rm -rf ~/Desktop/CalculatorC.app ../build

dvi: 
	@open instructions.md 

dist: 
	@mkdir -p ../dist
	@cp -R ../build/$(TARGET).app ../dist
	@cd ../dist && tar cvzf $(TARGET)_v1.0.tgz *
	@cd ../dist && rm -rf $(TARGET).app

test: 
ifeq ($(OS), Darwin)
	@gcc $(WWW) $(SRC) $(SRC_TEST) -o test.out $(LC) -lm
else
	@gcc $(WWW) $(SRC) $(SRC_TEST) -o test.out $(LC) $(UNIX)
endif
	@./test.out

gcov_report: clean
ifeq ($(OS), Darwin)
	@gcc $(WWW) $(GCOV) $(SRC) $(SRC_TEST) -o test.out $(LC)
else
	@gcc $(WWW) $(GCOV) $(SRC) $(SRC_TEST) -o test.out $(LC) $(UNIX)
endif
	@./test.out
	@lcov -t "test" -o test.info -c -d .
	@genhtml -o report test.info
	@$(OPEN_CMD) ./report/index.html
	@make clean_test

style:
	@cp ../materials/linters/.clang-format .
	@clang-format -n *.c **/*.c **/*.h **/*.cpp
	@rm ./.clang-format

clean: 
	@rm -rf *.o back/*.o *.a *.gch *.dSYM report  

clean_test:
	@rm -rf *.gcda *.gcno test.out *.info



