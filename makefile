#make compile to compile files
#make run to run the program
#make clean to remove the file goods

CC = gcc
CFLAGS := -std=c99 -Wall
RUN := ./goods

.PHONY: clean
	
clean: 
	-rm -f goods

compile:
	$(CC) $(CFLAGS) -o goods goods.c goods_input.c goods_db.c

run: compile
	$(RUN)

