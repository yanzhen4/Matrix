INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -stdlib=libc++ -lc++abi -g -O0 -Wall -Wextra -Werror -pedantic $(INCLUDES)
CXX=clang++

exec: run_exec

tests Matrix: bin/Matrix_tests.out
	-$<

tests Fraction: bin/Fraction_tests.out
	-$<

run_exec: bin/main.out
	$<

open_exec: 
	./bin/main.out

clean:
	rm -f bin/*

bin/main.out: src/main.cc src/matrix.cc src/fraction.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/Matrix_tests.out: tests/tests_matrix.cc src/matrix.cc src/fraction.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/Fraction_tests.out: tests/tests_fraction.cc src/matrix.cc src/fraction.cc
	$(CXX) $(CXXFLAGS) $^ -o $@


.DEFAULT_GOAL := exec
.PHONY: clean exec 