CXX=clang++
CXX_FLAGS=-std=c++20 -Iincludes -g -fstandalone-debug -O0 -Wall -Wextra -Werror

main: ./main

./main: ./src/main.cc ./src/matrix.cc
	$(CXX) $(CXX_FLAGS) $^ -o $@
clean:
	rm -f bin/*
