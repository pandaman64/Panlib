CXXFLAGS+=-std=c++11 -Wall -MMD -g

OBJS=main.o

main: $(OBJS)
	cc -o main $(OBJS) -lstdc++

run: main
	./main.exe

clean:
	rm -f *.d
	rm -f *.o
	rm -f *.exe

-include *.d

