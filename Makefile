all:
	g++ -g -std=c++11 -pedantic -Wall -Wextra -Wno-unused-const-variable -Wno-unused-parameter main.cpp
	./a.out < input.txt

diff:
	g++ -g -std=c++11 -pedantic -Wall -Wextra main.cpp
	./a.out < input.txt > output.txt
	diff output.txt solution.txt

go:
	@LOCAL=true go run main.go < input.txt
