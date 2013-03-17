CXXFLAGS=-std=c++11 -Wall -MMD

OBJS=main.o

main: $(OBJS)
	cc -o main main.o -lstdc++

run: main
	./main.exe

clean:
	rm -f *.d
	rm -f *.o
	rm -f *.exe

-include *.d 

