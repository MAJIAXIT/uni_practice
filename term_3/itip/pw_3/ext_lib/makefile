CC = g++-13

main :
	g++-13 -c funcs.cpp -fPIC -o funcs.o
	g++-13 -shared funcs.o -o libfuncs.so
	mv libfuncs.so ../