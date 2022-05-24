CFLAGS= -Wall -Wextra -g -std=c++17 -fsanitize=address

all: clean ecosystem
	./eco

ecosystem:
	c++ $(CFLAGS) ecosystem.cpp -o eco


clean:
	rm -f eco