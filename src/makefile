CC = gcc
AUTOR = thucydil AKA Darkhan-Sol0 & hollisgr
VERSION = 0.69
BRANCH = develop

PROG_NAME = s21_maze
VER = 1.01
CFLAGS = -I inc -std=c11 -Wall -Werror -Wextra
OBJECT = s21_maze.a
LIBSFLAGS = -lcheck -lncurses -lm -lsubunit
SANITIZER = -fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable
TEST_FILES = testfiles/*.c
SOURCE = functions/*.c
VALGRIND_LOG =  valgrind --tool=memcheck --leak-check=yes -q --log-file="log_valgrind.txt"
VALGRIND =  valgrind --tool=memcheck --leak-check=yes
CLANG = clang-format -style=Google

all: clean $(OBJECT) install

$(OBJECT): clean
	$(CC) $(CFLAGS) -c $(SOURCE)
	ar r $(OBJECT) *.o
	ranlib $(OBJECT)
	rm -rf *.o

run:
	./maze

install: clean $(OBJECT)
	$(CC) $(CFLAGS) -o maze maze.c $(OBJECT) $(LIBSFLAGS)

uninstall:
	rm -rf maze

valgrind: clean $(OBJECT)
	$(CC) $(CFLAGS) -o game brickgame.c $(OBJECT) $(LIBSFLAGS)
	$(VALGRIND_LOG) maze

test: clean_test $(OBJECT)
	$(CC) $(CFLAGS) -o test $(TEST_FILES) $(SOURCE) $(LIBSFLAGS)
	./test

test_valgrind: clean_test $(OBJECT)
	$(CC) $(CFLAGS) -o test $(TEST_FILES) $(OBJECT) $(LIBSFLAGS)
	$(VALGRIND) ./test

clean: clean_report clean_test
	rm -rf $(OBJECT) *.o maze TESEI_AI.txt generate_maze.txt

clean_test:
	rm -rf test

clean_report:
	rm -rf *.gcno *.gcda *.html *.css GCOVRreport lcov_report coverage.info

checkformat:
	$(CLANG) -n functions/*.c maze.c
	$(CLANG) -n inc/*.h
	$(CLANG) -n testfiles/*.c testfiles/*.h

setformat:
	$(CLANG) -i functions/*.c maze.c
	$(CLANG) -i inc/*.h
	$(CLANG) -i testfiles/*.c testfiles/*.h

report: gcov_report

openreport:
	firefox GCOVRreport/gcov_report.html

gcov_report: clean_test clean_report $(OBJECT)
	gcc -I inc --coverage $(SOURCE) ${TEST_FILES} -o test $(OBJECT) $(LIBSFLAGS)
	./test
	~/.local/bin/gcovr -r . --html-details -o gcov_report.html
	# gcovr -r . --html-details -o gcov_report.html
	mkdir GCOVRreport
	mv *.html *.css GCOVRreport
	rm -rf *.gcno *.gcda

lcov_report: clean_test clean_report
	gcc -I inc --coverage $(SOURCE) ${TEST_FILES} -o test $(OBJECT) $(LIBSFLAGS)
	./test
	lcov -t "Report" -c -d ./ --output-file ./coverage.info
	genhtml coverage.info --output-directory lcov_report/
	rm -rf *.gcno *.gcda

help:
	@echo
	@echo "		Hello, world! Welcome to s21_maze!"
	@echo
	@echo "		Usage: make [option]"
	@echo "		<test> 						Run tests"
	@echo "		<test_valgrind> 			Run tests with valgrind"
	@echo "		<report> or <gcov_report> 	Builds GCOVr report"
	@echo "		<openreport> 		 		Use it after building report for open page on firefox browser"
	@echo "		<checkformat> 				Make style check based of Google-style"
	@echo

commit:
	@read -p "Enter commit message: " input; \
	git add -A; \
	git commit -m "$$input - $(PROG_NAME) v:$(VERSION) - $(shell date +'%Y-%m-%d %H:%M')"; \
	git push origin $(BRANCH)
