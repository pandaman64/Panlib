CXXFLAGS+=-std=c++11 -Wall -MMD
OBJS=main.o

main: $(OBJS)
	cc -o main $(OBJS) -lstdc++

clean:
	rm -f *.d
	rm -f *.o
	rm -f *.exe

run: main
	./main.exe

-include *.d

