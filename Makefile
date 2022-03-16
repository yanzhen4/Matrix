INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -stdlib=libc++ -lc++abi -g -O0 -Wall -Wextra -Werror -pedantic $(INCLUDES)
CXX=clang++

exec: run_exec

tests: run_tests 

run_exec: bin/main.out
	$<

run_tests: bin/tests.out
	- $<

open_exec: 
	./bin/main.out

clean:
	rm -f bin/*

bin/main.out: src/main.cc src/matrix.cc src/fraction.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests.out: tests/tests.cc src/matrix.cc src/fraction.cc
	$(CXX) $(CXXFLAGS) $^ -o $@


.DEFAULT_GOAL := exec
.PHONY: clean exec 