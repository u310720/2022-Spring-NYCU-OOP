all:
	g++ -c -g Mempool.cpp
	g++ -c -g Minner.cpp	
	g++ -c -g functions.cpp
	g++ -o p04 main.cpp Mempool.o functions.o Minner.o
clean:
	rm *.o p04
d01:
	./p04 trans.txt miners.txt 5
d02:
	./p04 trans.txt miners.txt 5
d03:
	valgrind ./p04 trans.txt miners.txt 5
