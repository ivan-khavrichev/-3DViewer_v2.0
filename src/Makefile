CXX = g++ -g
STD = -std=c++17
CXXFLAGS = -Wall -Werror -Wextra
LINKER_OPTIONS = -lgtest
PATH_BACK = 3dviewer_v2/back/
PATH_FRONT = 3dviewer_v2/front/
CC_FILES = $(wildcard 3dviewer_v2/back/*.cc)
OBJ_FILES = $(wildcard *.o)
TEST_CC_FILES = $(wildcard tests.cc)
TEST_OBJ_FILES = $(patsubst %.cc, %.o, $(TEST_CC_FILES))
WSL_LINK_FLAGS = -lsubunit `pkg-config --cflags --libs check`
TRASH = $(wildcard *.o *.a *.gc* *.out *.tar Documentation html doxyconfig.bak latex tests test.info report $(PATH_BACK)*.o *.dSYM models/*.gif models/*.bmp models/*.jpeg .clang-format)
UNAME = $(shell uname -s)

all: install
ifeq ($(UNAME), Linux)
	cd build && ./3dviewer_v2
endif

open:
	./build/3dviewer_v2.app/Contents/MacOS/3dviewer_v2

install:
	mkdir build
	cd build; cmake ../3dviewer_v2 -Wno-dev
	cd build && make
	
uninstall: clean
	rm -rf 3dviewer_v2/CMakeLists.txt.user
	rm -rf build

rebuild: uninstall install

dvi:
	doxygen doxyconfig
	open ./html/index.html

dvi_clean:
	rm -rf doxyconfig.bak
	rm -rf html
	rm -rf latex

dist:
	rm -rf dist_archive.tar
	cp ../materials/linters/.clang-format ./
	tar -cf dist_archive.tar 3dviewer_v2/ Makefile models/ doxyconfig tests.cc .clang-format
	rm -rf clang-format

clean: pure dvi_clean uninstall

viewer:
	$(CXX) $(STD) -c $(CXXFLAGS) $(CC_FILES)

test: viewer
ifeq ($(UNAME), Linux)
	$(CXX) $(STD) $(CXXFLAGS) -c $(TEST_CC_FILES) $(LINKER_OPTIONS) $(WSL_LINK_FLAGS)
	$(CXX) $(STD) $(CXXFLAGS) $(OBJ_FILES) -o tests $(LINKER_OPTIONS) $(WSL_LINK_FLAGS)
	./tests
else
	$(CXX) $(STD) $(CXXFLAGS) -c $(TEST_CC_FILES) $(LINKER_OPTIONS)
	$(CXX) $(STD) $(CXXFLAGS) $(OBJ_FILES) -o tests  $(LINKER_OPTIONS) 
	./tests
endif

gcov_report:
ifeq ($(UNAME), Linux)
	$(CXX) $(STD) --coverage $(CC_FILES) $(TEST_CC_FILES) $(LINKER_OPTIONS)  -o tests
else
	$(CXX) $(STD) --coverage $(CC_FILES) $(TEST_CC_FILES) $(LINKER_OPTIONS) -o tests
endif
	./tests
	lcov -t "test" --no-external -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

check_style:
	cp ../materials/linters/.clang-format ../src
	clang-format -n -style=google *.cc $(PATH_BACK)*.cc $(PATH_BACK)*.h $(PATH_FRONT)*.cc $(PATH_FRONT)*.h 3dviewer_v2/main.cc
	rm -rf .clang-format

correct_style:
	cp ../materials/linters/.clang-format ../src
	clang-format -i -style=google *.cc $(PATH_BACK)*.cc $(PATH_BACK)*.h $(PATH_FRONT)*.cc $(PATH_FRONT)*.h 3dviewer_v2/main.cc
	rm -rf .clang-format

check_mem: clean test
ifeq ($(UNAME), Linux)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./tests
else
	leaks -atExit -- ./tests
endif

pure:
	rm -rf $(TRASH)

rebuild: uninstall all
