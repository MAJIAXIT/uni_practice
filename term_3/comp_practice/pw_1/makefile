CC = clang-17

P_SRC = ./src/
P_OBJ = ./obj/

task1 : $(P_SRC)1.c
	$(CC) -E     $(P_SRC)1.c -o $(P_OBJ)1.i
	$(CC) -S     $(P_SRC)1.c -o $(P_OBJ)1.s
	$(CC) -c     $(P_SRC)1.c -o $(P_OBJ)1.o
	$(CC) -S 	 $(P_SRC)1.c -o $(P_OBJ)optim.s
	$(CC) -S -O1 $(P_SRC)1.c -o $(P_OBJ)optim1.s 
	$(CC) -S -O2 $(P_SRC)1.c -o $(P_OBJ)optim2.s 
	$(CC) -S -O3 $(P_SRC)1.c -o $(P_OBJ)optim3.s
	$(CC)		 $(P_OBJ)1.o -o $(P_OBJ)1

task2 : $(P_SRC)2.c $(P_SRC)3.c
	$(CC)  -c $(P_SRC)arr.c -o $(P_OBJ)arr.o
	$(CC)  -c $(P_SRC)io.c  -o $(P_OBJ)io.o
	$(CC)  -c $(P_SRC)2.c   -o $(P_OBJ)2.o 
	$(CC)  -c $(P_SRC)3.c   -o $(P_OBJ)3.o
	$(CC)  $(P_OBJ)arr.o $(P_OBJ)io.o $(P_OBJ)2.o -o $(P_OBJ)2
	$(CC)  $(P_OBJ)arr.o $(P_OBJ)io.o $(P_OBJ)3.o -o $(P_OBJ)3
	ar crs $(P_OBJ)libarr.a $(P_OBJ)arr.o $(P_OBJ)io.o
	$(CC)  $(P_OBJ)3.o -L$(P_OBJ) -larr -o $(P_OBJ)3
	$(CC)  $(P_OBJ)3.o -L$(P_OBJ) -larr -o $(P_OBJ)3

clean :
	rm $(P_OBJ)*