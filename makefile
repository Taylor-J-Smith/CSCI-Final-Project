compiler = gcc
args = -Wall -Wextra -std=c99
libs = -lm

all: run

compile:
	@$(compiler) $(args) -o main main.c $(libs)

run: compile
	./main 50

clean:
	rm -f main

time: compile
	time --output=times-seq.txt -p -a ./main 1000000000
	echo "" >> times-seq.txt
