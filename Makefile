CC = clang
# -g
override CFLAGS += -Wall -Wextra -Wpedantic -O3

##! DO NOT BELOW TOUCH THIS!
##! this took ages to work out (Makefile is annoying)
##! so i dont want to have to reinvent the contents of this file!

SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print)
OBJS = $(patsubst src/%.c, target/%.o, $(patsubst ./src/%.c, ./target/%.o, $(SRCS)))
# OBJS = $(patsubst %.c, %.o, $(SRCS))


./target/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o target/main

clean:
	rm -f $(OBJS) main target/main

.PHONY: main clean
