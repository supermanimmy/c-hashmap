CC = gcc
CFLAGS_DEBUG = -g -Wall 
CFLAGS_RELEASE = -O3 -Wall -Wextra -Werror -Wshadow -march=native
CFLAGS_TEST = -O0 -Wall -Wextra -Werror -Wshadow -march=native -fprofile-arcs -ftest-coverage


LIBTYPE ?= STATIC
NAME ?= hashmap


FILES = \
	$(wildcard src/*.c) \

FILES_TEST = \
	$(FILES) \
	$(wildcard tests/*.c) \


ifeq ($(OS),Windows_NT)
	PLATFORM_OS = WINDOWS
else
	PLATFORM_OS = LINUX
endif


ifeq ($(LIBTYPE),SHARED)
	ifeq ($(PLATFORM_OS),WINDOWS)
		LIBNAME = lib$(NAME).dll
	endif
	ifeq ($(PLATFORM_OS),LINUX)
		LIBNAME = lib$(NAME).so
	endif
    CFLAGS_RELEASE = -o $(LIBNAME) $(CFLAGS_RELEASE) -shared
endif
ifeq ($(LIBTYPE),STATIC)
    CFLAGS_RELEASE += -c
	LIBNAME = lib$(NAME).a
endif


build:
	$(CC) $(FILES) $(CFLAGS_RELEASE)
ifeq ($(LIBTYPE),STATIC)
	ar -rc $(LIBNAME) *.o
endif


test: clean build
	$(CC) -o test $(FILES_TEST) $(CFLAGS_TEST)
	./test
	gcovr -e "tests/*" --xml-pretty --exclude-unreachable-branches --print-summary -o coverage.xml


memcheck: clean build
	$(CC) -o test $(FILES_TEST) $(CFLAGS_TEST) -l$(NAME) -L.
	valgrind --leak-check=full ./test


clean:
ifeq ($(PLATFORM_OS),WINDOWS)
	del *.o *.exe *.dll *.so *.out.* *.a *.gcda *.gcno /s
else
	rm -fv *.o *.exe *.dll *.so *.out.* *.a *.gcda *.gcno
endif
