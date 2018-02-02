all:
	g++ -g -std=c++11 -pedantic -Wall -Wextra main.cpp
	./a.out < input.txt

go:
	@LOCAL=true go run main.go < input.txt
