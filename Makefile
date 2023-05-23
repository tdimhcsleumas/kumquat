EXEC = a.out
SRC = $(shell find ./src -name "*.c" -o -name "*.h")
CXX = clang
CXX_OPTIONS = -std=c99 -g -O2 -Wall -Wextra -Wpedantic -Wshadow -Werror -fsanitize=address -lm 

all : ${EXEC}

${EXEC} : ${SRC}
	${CXX} $^ ${CXX_OPTIONS} 

clean :
	rm -rf ${EXEC}
