CC = g++-13

main :
	$(CC) -c arr.cpp -fPIC -o arr.o
	$(CC) -shared arr.o -o libarr.so
	mv libarr.so ../