CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -g -fstandalone-debug -Wall -Wextra -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: ./src/main.cc ./src/matrix.cc ./includes/matrix.hpp ./src/fraction.cc ./includes/fraction.hpp
	$(CXX) $(CXXFLAGS) ./src/main.cc ./src/matrix.cc ./src/fraction.cc  -o $@

bin/tests: ./tests/tests.cc ./src/matrix.cc ./includes/matrix.hpp ./src/fraction.cc ./includes/fraction.hpp
	$(CXX) $(CXXFLAGS) ./tests/tests.cc ./src/matrix.cc ./src/fraction.cc  -o $@


.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -rf ./bin/*