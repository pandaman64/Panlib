CXXFLAGS+=-std=c++11 -Wall -MMD

test: test.o
	cc -o test test.o -lstdc++

run : test
	./test.exe

clean:
	rm -f *.d
	rm -f *.o
	rm -f *.exe

-include *.d

