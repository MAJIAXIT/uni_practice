CC = clang-17

P_OBJ = ./obj/
P_SRC = ./src/

all: task1 task2 task3

task1 : $(P_SRC)1.c
	$(CC) $(P_SRC)1.c -g -o $(P_OBJ)1

task2 : $(P_SRC)2.c
	$(CC) $(P_SRC)2.c -g -o $(P_OBJ)2

task3 : $(P_SRC)3.c
	$(CC) -c -g $(P_SRC)str.c -o $(P_OBJ)str.o
	ar crs $(P_OBJ)libstr.a $(P_OBJ)str.o
	$(CC) $(P_SRC)3.c -g -L$(P_OBJ) -lstr -o $(P_OBJ)3

clean :
	rm -r $(P_OBJ)*