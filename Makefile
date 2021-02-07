.PHONY: all diff build go

all: build
	./a.out < input.txt

diff: build
	./a.out < input.txt > output.txt
	diff output.txt solution.txt

build:
	g++ -g -std=c++11 -pedantic -Wall -Wextra -Wno-unused-const-variable -Wno-unused-parameter main.cpp

go:
	@LOCAL=true go run main.go < input.txt
