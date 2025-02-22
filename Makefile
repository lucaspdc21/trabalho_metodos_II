all: main.o

main.o:
	g++ main.cpp -o main.o
clean:
	rm -rf *.o